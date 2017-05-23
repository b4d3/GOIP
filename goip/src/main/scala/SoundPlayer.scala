import java.io._
import java.net.SocketException
import javax.sound.sampled._

/**
  * Created by bade on 20.05.17..
  */
class SoundPlayer(inputStream: InputStream) {

  private val format = SoundUtil.getAudioFormat
  @volatile private var stopped = false
  private val audioBytes = new Array[Byte](SoundUtil.BUFFER_SIZE)

  val info = new DataLine.Info(classOf[SourceDataLine], format)
  require(AudioSystem.isLineSupported(info), "The system does not support the specified format.")

  private val audioLine = AudioSystem.getSourceDataLine(format)

  def start(): Unit = {

    stopped = false
    audioLine.open()
    audioLine.start()
    var numBytesRead = inputStream.read(audioBytes)

    while (!stopped && numBytesRead != -1) {
      audioLine.write(audioBytes, 0, numBytesRead)
      try {
        numBytesRead = inputStream.read(audioBytes)
      } catch {
        case e: SocketException => println("Closed connection")
      }
    }
  }

  def stop(): Unit = {
    stopped = true

    if (audioLine != null) {
      audioLine.drain()
      audioLine.close()
    }
  }
}