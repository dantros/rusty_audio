#include <rusty_audio.h>
#include <thread>
#include <chrono>

int main()
{
    RustyAudio::AudioBuffer audioBuffer;

    int deltaTime = 33 * 30 * 15;
    float deltaTimeFloat = static_cast<float>(deltaTime);
    std::chrono::milliseconds duration{ deltaTime };

    std::this_thread::sleep_for(duration);
}