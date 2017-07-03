import java.io._
import java.net.SocketException
import javax.sound.sampled._

/**
  * Created by bade on 21.05.17..
  */
/**
  * Records the sound obtained from line-in (microphone) and sends audio data to output stream
  * @param outputStream Output stream that the recorded audio data is sent to
  */
class SoundRecorder(outputStream: OutputStream) {

  private val format = SoundUtil.getAudioFormat
  @volatile private var stopped = false
  private val audioBytes = new Array[Byte](SoundUtil.BUFFER_SIZE)

  val info = new DataLine.Info(classOf[TargetDataLine], format)
  require(AudioSystem.isLineSupported(info), "The system does not support the specified format.")

  private val audioLine = AudioSystem.getTargetDataLine(format)

  /**
    * Starts recording audio data got from line-in (microphone)
    * @todo Maybe calling this method when pressing a 'play' button on GUI
    */
  def start(): Unit = {

    stopped = false

    // Opens the audio line (acquires required resources), but starts recording only on start() method
    audioLine.open()

    // Starts recording a sound
    audioLine.start()

    var numBytesRead = audioLine.read(audioBytes, 0, SoundUtil.BUFFER_SIZE)

    while (!stopped && numBytesRead != -1) {
      try {
        outputStream.write(audioBytes)
      } catch {
        case e: SocketException => {
          println("Closed connection: " + e.getMessage)
          stop()
        }
      }
      numBytesRead = audioLine.read(audioBytes, 0, SoundUtil.BUFFER_SIZE)
    }
  }

  /**
    * Stops recording the sound. Safe to call start() again
    * @todo Maybe calling this method by pressing a 'stop' or 'close' button on GUI
    */
  def stop(): Unit = {

    stopped = true

    if (outputStream != null) {
      outputStream.flush()
    }

    if (audioLine != null) {
      audioLine.drain()
      audioLine.close()
    }
  }

}
