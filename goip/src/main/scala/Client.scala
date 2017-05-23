import java.net.{InetAddress, Socket}

/**
  * Created by bade on 20.05.17..
  */
object Client extends App {
  val socket = new Socket(InetAddress.getByName("localhost"), 1234)

  val in = socket.getInputStream
  val out = socket.getOutputStream

  val soundPlayer = new SoundPlayer(in)
  val soundRecorder = new SoundRecorder(out)

  private def startConversation = {
    new Thread(new Runnable {
      override def run(): Unit = soundPlayer.start()
    }).start()

    new Thread(new Runnable {
      override def run(): Unit = soundRecorder.start()
    }).start()
  }

  private def stopConversation = {
    soundRecorder.stop()
    soundPlayer.stop()
  }

  startConversation

  Thread.sleep(2000)
  stopConversation

  startConversation

  Thread.sleep(2000)
  stopConversation

  in.close()
  out.close()
}
