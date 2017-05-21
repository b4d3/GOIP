import javax.sound.sampled.*;
import java.io.File;
import java.io.IOException;

/**
 * Created by bade on 20.05.17..
 */
public class SoundPlayer2 {

    private AudioFormat format;
    private SourceDataLine line;
    private boolean stopped;

    /**
     * Defines a default audio format used to record
     */
    AudioFormat getAudioFormat() {
        float sampleRate = 44100;
        int sampleSizeInBits = 16;
        int channels = 2;
        boolean signed = true;
        boolean bigEndian = true;
        return new AudioFormat(sampleRate, sampleSizeInBits, channels, signed,
                bigEndian);
    }

    public void start() throws LineUnavailableException {

//        format = getAudioFormat();

        DataLine.Info info = new DataLine.Info(SourceDataLine.class, format);

        if (!AudioSystem.isLineSupported(info)) {
            throw new LineUnavailableException("The system does not support the specified format.");
        }

        File fileIn = new File("Record.wav");
        try {
            AudioInputStream audioInputStream = AudioSystem.getAudioInputStream(fileIn);

            format = audioInputStream.getFormat();
            line = AudioSystem.getSourceDataLine(format);
            line.open(format);

            int bytesPerFrame =
                    audioInputStream.getFormat().getFrameSize();
            // Set an arbitrary buffer size of 1024 frames.
            int numBytes = line.getBufferSize(); //1024 * bytesPerFrame;
            byte[] audioBytes = new byte[numBytes];
            int numBytesRead = 0;

            stopped = false;
            line.start();

            // Try to read numBytes bytes from the file.
            while (!stopped && (numBytesRead =
                    audioInputStream.read(audioBytes)) != -1) {
                line.write(audioBytes, 0, numBytesRead);
            }
        } catch (UnsupportedAudioFileException | IOException e) {
            System.err.println(e.getMessage());
            line.close();
        }
    }

    public void stop() {

        stopped = true;

        if (line != null) {
            line.drain();
            line.close();
        }
    }

}
