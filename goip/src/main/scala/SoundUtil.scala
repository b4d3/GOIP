import javax.sound.sampled.AudioFormat

object SoundUtil {

  val BUFFER_SIZE = 4096

  /**
    * Defines a default audio format used to record
    */
  def getAudioFormat: AudioFormat = {
    val sampleRate = 44100
    val sampleSizeInBits = 16
    val channels = 2
    val signed = true
    val bigEndian = true
    new AudioFormat(sampleRate, sampleSizeInBits, channels, signed, bigEndian)
  }

}