import java.io.File
import java.net.ServerSocket
import javax.sound.sampled._

import Client.fileIn

/**
  * Created by bade on 20.05.17..
  */
class Peer(port: Int) {

  private val BUFFER_SIZE = 4096

//  val format = SoundUtil.getAudioFormat
  val format = AudioSystem.getAudioInputStream(new File("Record.wav")).getFormat

  val data = Array.ofDim[Byte](BUFFER_SIZE)

  val info = new DataLine.Info(classOf[SourceDataLine], format)

  if (!AudioSystem.isLineSupported(info)) throw new LineUnavailableException("The system does not support the specified format.")

  val inputAudioLine = AudioSystem.getSourceDataLine(format)

  inputAudioLine.open(format)
  inputAudioLine.start()

  val server = new ServerSocket(port)

  val client = server.accept

  val in = client.getInputStream

//  val soundPlayer = new SoundPlayer(in)
//  soundPlayer.start()

  var numOfBytesRead = in.read(data)

  while (numOfBytesRead != -1) {
    inputAudioLine.write(data, 0, numOfBytesRead)
    numOfBytesRead = in.read(data)
  }
}
