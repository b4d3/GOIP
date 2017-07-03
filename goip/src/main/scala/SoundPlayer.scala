import java.io._
import java.net.SocketException
import javax.sound.sampled._

/**
  * Created by bade on 20.05.17..
  */
/**
  * Reproduces the audio stream
  * @param inputStream Input stream where the audio data is read from
  */
class SoundPlayer(inputStream: InputStream) {

  private val format = SoundUtil.getAudioFormat
  @volatile private var stopped = false
  private val audioBytes = new Array[Byte](SoundUtil.BUFFER_SIZE)

  val info = new DataLine.Info(classOf[SourceDataLine], format)
  require(AudioSystem.isLineSupported(info), "The system does not support the specified format.")

  private val audioLine = AudioSystem.getSourceDataLine(format)

  /**
    * Starts reproducing audio data got from input stream
    * @todo Maybe calling this method when pressing a 'play' button on GUI
    */
  def start(): Unit = {

    stopped = false

    // Opens the audio line (acquires required resources), but starts playing only on start() method
    audioLine.open()

    // Starts reproducing a sound
    audioLine.start()

    var numBytesRead: Int = 0

    try {
      numBytesRead = inputStream.read(audioBytes)
    } catch {
      case e: SocketException => {
        println("No connection: " + e.getMessage)
        return
      }
    }

    while (!stopped && numBytesRead != -1) {
      audioLine.write(audioBytes, 0, numBytesRead)
      try {
        numBytesRead = inputStream.read(audioBytes)
      } catch {
        case e: SocketException => {
          println("Closed connection: " + e.getMessage)
          return
        }
      }
    }
  }

  /**
    * Stops reproducing the sound. Safe to call start() again
    * @todo Maybe calling this method by pressing a 'stop' or 'close' button on GUI
    */
  def stop(): Unit = {

    stopped = true

    if (audioLine != null) {
      // Make sure the drain() method is called after the input stream has been called!
      // Otherwise, causes thread starvation!
      audioLine.drain()

      audioLine.close()
    }
  }
}