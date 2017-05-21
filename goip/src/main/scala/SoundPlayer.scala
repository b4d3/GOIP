import javax.sound.sampled._
import java.io.{File, IOException, InputStream}

import Client.fileIn

/**
  * Created by bade on 20.05.17..
  */
class SoundPlayer(inputStream: InputStream) {

//  private val format = SoundUtil.getAudioFormat
  private var stopped = false
  private val format = AudioSystem.getAudioInputStream(new File("Record.wav")).getFormat

  val info = new DataLine.Info(classOf[SourceDataLine], format)
  require(AudioSystem.isLineSupported(info), "The system does not support the specified format.")

  private val audioLine = AudioSystem.getSourceDataLine(format)

  def start(): Unit = {

    val audioBytes = new Array[Byte](SoundUtil.BUFFER_SIZE)
    stopped = false
    audioLine.start()
    var numBytesRead = inputStream.read(audioBytes)

    while (!stopped && numBytesRead != -1) {
      audioLine.write(audioBytes, 0, numBytesRead)
      inputStream.read(audioBytes)
//      numBytesRead = inputStream.read(audioBytes)
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