import java.io.{File, IOException}
import java.net.{InetAddress, Socket}
import javax.sound.sampled._

import scala.io.BufferedSource

/**
  * Created by bade on 20.05.17..
  */
object Client extends App {
  val socket = new Socket(InetAddress.getByName("localhost"), 1234)
  val out = socket.getOutputStream

  val fileIn = new File("Record.wav")
  try {
    val audioInputStream = AudioSystem.getAudioInputStream(fileIn)
    val format = audioInputStream.getFormat

    val audioBytes = new Array[Byte](4096)
    var numBytesRead = audioInputStream.read(audioBytes)
    // Try to read numBytes bytes from the file.
    while (numBytesRead != -1) {
      out.write(audioBytes, 0, numBytesRead)
      numBytesRead = audioInputStream.read(audioBytes)
    }

  } catch {
    case e@(_: UnsupportedAudioFileException | _: IOException) =>
      System.err.println(e.getMessage)
  }
}
