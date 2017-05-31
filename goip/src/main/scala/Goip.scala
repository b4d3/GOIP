/**
  * Created by bade on 31.05.17..
  */
object Goip extends App {

  private val peer = new Peer

  val (t1, t2) = peer.startConversation

  t1.join()
  t2.join()

}
