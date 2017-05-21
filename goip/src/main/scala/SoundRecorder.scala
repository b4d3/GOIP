import java.io._
import java.net.SocketException
import javax.sound.sampled._

/**
  * Created by bade on 21.05.17..
  */
class SoundRecorder(outputStream: OutputStream) {

  private val format = SoundUtil.getAudioFormat
  @volatile private var stopped = false

  val info = new DataLine.Info(classOf[TargetDataLine], format)
  require(AudioSystem.isLineSupported(info), "The system does not support the specified format.")

  private val audioLine = AudioSystem.getTargetDataLine(format)

  def start(): Unit = {

    val audioBytes = new Array[Byte](SoundUtil.BUFFER_SIZE)
    stopped = false
    audioLine.open()
    audioLine.start()

    var numBytesRead = audioLine.read(audioBytes, 0, SoundUtil.BUFFER_SIZE)

    while (!stopped && numBytesRead != -1) {
      try {
        outputStream.write(audioBytes)
      } catch {
        case e: SocketException => {
          println("Closed connection")
          stop()
        }
      }
      numBytesRead = audioLine.read(audioBytes, 0, SoundUtil.BUFFER_SIZE)
    }

    audioLine.close()
    outputStream.close()
  }

  def stop(): Unit = {
    stopped = true

    if (audioLine != null) {
      audioLine.drain()
    }

    if (outputStream != null) {
      outputStream.flush()
    }
  }
}
