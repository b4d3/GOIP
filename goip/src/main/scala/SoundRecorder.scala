import java.io._
import java.net.SocketException
import javax.sound.sampled._

/**
  * Created by bade on 21.05.17..
  */
class SoundRecorder(outputStream: OutputStream) {

  private val format = SoundUtil.getAudioFormat
  @volatile private var stopped = false
  private val audioBytes = new Array[Byte](SoundUtil.BUFFER_SIZE)

  val info = new DataLine.Info(classOf[TargetDataLine], format)
  require(AudioSystem.isLineSupported(info), "The system does not support the specified format.")

  private val audioLine = AudioSystem.getTargetDataLine(format)

  def start(): Unit = {

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
  }

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
