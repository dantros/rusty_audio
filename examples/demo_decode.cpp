
#include <rusty_audio.h>
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: demo_decode <audio_file>" << std::endl;
        std::cout << "Supported formats: WAV, FLAC, MP3" << std::endl;
        return 1;
    }

    const char* filePath = argv[1];
    std::cout << "Decoding: " << filePath << std::endl;

    RustyAudio::Buffer soundBuffer = RustyAudio::decodeAudioFromFile(filePath);

    if (soundBuffer.size() == 0)
    {
        std::cout << "Failed to decode audio file." << std::endl;
        return 1;
    }

    std::cout << "Sample rate: " << soundBuffer.sampleRate() << " Hz" << std::endl;
    std::cout << "Channels:    " << soundBuffer.channels() << std::endl;
    std::cout << "Frames:      " << soundBuffer.frames() << std::endl;
    std::cout << "Duration:    " << soundBuffer.duration() << " ms" << std::endl;
    std::cout << std::endl;

    RustyAudio::Player soundPlayer;
    soundPlayer.init(soundBuffer);

    std::cout << "Press enter to play";
    getchar();
    soundPlayer.play();

    std::cout << "Press enter to pause";
    getchar();
    soundPlayer.pause();

    std::cout << "Press enter to continue";
    getchar();
    soundPlayer.play();

    std::cout << "Press enter to stop";
    getchar();
    soundPlayer.stop();

    std::cout << "Press enter to play again";
    getchar();
    soundPlayer.play();

    std::cout << "Press enter to finish";
    getchar();
    soundPlayer.stop();
}
