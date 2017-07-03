import java.io.{InputStream, OutputStream}
import java.net.{InetAddress, Socket}

/**
  * Created by bade on 20.05.17..
  */
/**
  * Represents the end client that records and plays the sound
  */
class Peer {

  val port: Int = new ConfigurationProvider("../config/config.json").getLocalPort
  val socket = new Socket(InetAddress.getByName("localhost"), port)

  val in: InputStream = socket.getInputStream
  val out: OutputStream = socket.getOutputStream

  val soundPlayer = new SoundPlayer(in)
  val soundRecorder = new SoundRecorder(out)

  /**
    * Starts the sound recording and reproducing
    * @return Tuple of recording and reproducing thread (used to manage the threads from calling thread)
    */
  def startConversation: (Thread, Thread) = {
    val playerThread = new Thread(() => soundPlayer.start())
    playerThread.start()

    val recorderThread = new Thread(() => soundRecorder.start())
    recorderThread.start()

    (playerThread, recorderThread)
  }

  /**
    * Stops the sound recording and reproducing
    * @todo Investigate the conversation restart (redundant thread creation?)
    */
  def stopConversation(): Unit = {
    soundRecorder.stop()
    soundPlayer.stop()
  }

  /**
    * Shuts down the end connection.
    * Called on program closing. Not safe to call startConversation() afterwards
    */
  def shutdown(): Unit = {
    in.close()
    out.close()
  }

}
