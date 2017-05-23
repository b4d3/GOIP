import java.net.ServerSocket

/**
  * Created by bade on 20.05.17..
  */
class Peer(port: Int) {

  val server = new ServerSocket(port)

  val client = server.accept

  val in = client.getInputStream
  val out = client.getOutputStream

  val soundPlayer = new SoundPlayer(in)
  val soundRecorder = new SoundRecorder(out)

  new Thread(new Runnable {
    override def run(): Unit = soundPlayer.start()
  }).start()

  new Thread(new Runnable {
    override def run(): Unit = soundRecorder.start()
  }).start()

  in.close()
  out.close()

}
