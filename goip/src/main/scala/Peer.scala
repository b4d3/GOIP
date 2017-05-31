import java.net.{InetAddress, Socket}

/**
  * Created by bade on 20.05.17..
  */
class Peer {

  val port = ConfigurationProvider.getLocalPort
  val socket = new Socket(InetAddress.getByName("localhost"), port)

  val in = socket.getInputStream
  val out = socket.getOutputStream

  val soundPlayer = new SoundPlayer(in)
  val soundRecorder = new SoundRecorder(out)

  def startConversation: (Thread, Thread) = {
    val playerThread = new Thread(() => soundPlayer.start())
    playerThread.start()

    val recorderThread = new Thread(() => soundRecorder.start())
    recorderThread.start()

    (playerThread, recorderThread)
  }

  def stopConversation = {
    soundRecorder.stop()
    soundPlayer.stop()
  }

  def shutdown: Unit = {
    in.close()
    out.close()
  }

}
