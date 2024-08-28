
#include <rusty_audio.h>
#include <iostream>
#include <thread>
#include <chrono>

int main()
{
    RustyAudio::SoundManager soundManager;

    // scheduling a bunch of notes...
    /*
    //Octava 4
    soundManager.scheduleNote(Note{ 1000, 1.0, 261.626 }); // Do
    soundManager.scheduleNote(Note{ 1000, 1.0, 293.665 }); // Re
    soundManager.scheduleNote(Note{ 1000, 1.0, 329.628 }); // Mi
    soundManager.scheduleNote(Note{ 1000, 1.0, 349.228 }); // Fa
    soundManager.scheduleNote(Note{ 1000, 1.0, 391.995 }); // Sol
    soundManager.scheduleNote(Note{ 1000, 1.0, 440.000 }); // La
    soundManager.scheduleNote(Note{ 1000, 1.0, 493.883 }); // Si
    //Octava 5
    soundManager.scheduleNote(Note{ 1000, 1.0, 523.251 }); // Do

    //Octava 4
    soundManager.scheduleNote(Note{ 500, 1.0, 261.626 }); // Do
    soundManager.scheduleNote(Note{ 500, 1.0, 293.665 }); // Re
    soundManager.scheduleNote(Note{ 500, 1.0, 329.628 }); // Mi
    soundManager.scheduleNote(Note{ 500, 1.0, 349.228 }); // Fa
    soundManager.scheduleNote(Note{ 500, 1.0, 391.995 }); // Sol
    soundManager.scheduleNote(Note{ 500, 1.0, 440.000 }); // La
    soundManager.scheduleNote(Note{ 500, 1.0, 493.883 }); // Si
    //Octava 5
    soundManager.scheduleNote(Note{ 500, 1.0, 523.251 }); // Do
    */
    //Octava 4
    /*soundManager.scheduleNote(RustyAudio::Note{250, 1.0, 261.626}); // Do
    soundManager.scheduleNote(RustyAudio::Note{ 250, 1.0, 293.665 }); // Re
    soundManager.scheduleNote(RustyAudio::Note{ 250, 1.0, 329.628 }); // Mi
    soundManager.scheduleNote(RustyAudio::Note{ 250, 1.0, 349.228 }); // Fa
    soundManager.scheduleNote(RustyAudio::Note{ 250, 1.0, 391.995 }); // Sol
    soundManager.scheduleNote(RustyAudio::Note{ 250, 1.0, 440.000 }); // La
    soundManager.scheduleNote(RustyAudio::Note{ 500, 1.0, 493.883 }); // Si
    */
    //Octava 5
    /*soundManager.scheduleNote(RustyAudio::Note{750, 1.0, 523.251}); // Do
    */
    

    int deltaTime = 33;
    float deltaTimeFloat = static_cast<float>(deltaTime);
    std::chrono::milliseconds duration{ deltaTime };

    // start to play the scheduled notes
    soundManager.playNext();

    // every 5 seconds we will schedule a new note.
    float millisCounter = 0.0;
    constexpr float MAX_MILLIS = 2000.0f;

    while (true)
    {
        // the tick is using floats as most likely you will handle delta times with floats instead of ints.
        // we update the sound manager with a time period, internally, it  will handle avancing to the next scheduled note if needed.
        soundManager.tick(deltaTimeFloat);

        // this is a simulation of other computing work, such as physics and graphics... it just take some time.
        std::this_thread::sleep_for(duration);

        // for debugging and understanding.
        std::cout << ".";


        // after some time, we schedule a new note.
        millisCounter += deltaTimeFloat;
        if (millisCounter > MAX_MILLIS)
        {
            std::cout << "scheduling new note" << std::endl;
            millisCounter = 0.0f;

            soundManager.scheduleNote(RustyAudio::Note{ 250, 1.0, 261.626 }); // Do
            soundManager.scheduleNote(RustyAudio::Note{ 250, 1.0, 293.665 }); // Re
            soundManager.scheduleNote(RustyAudio::Note{ 250, 1.0, 329.628 }); // Mi
            soundManager.scheduleNote(RustyAudio::Note{ 250, 1.0, 349.228 }); // Fa
            soundManager.scheduleNote(RustyAudio::Note{ 250, 1.0, 391.995 }); // Sol
            soundManager.scheduleNote(RustyAudio::Note{ 250, 1.0, 440.000 }); // La
            soundManager.scheduleNote(RustyAudio::Note{ 250, 1.0, 493.883 }); // Si
            soundManager.playNext();
        }

        // we break the loop when we decide to finish the program, here we just never finish.
    }

    std::cout << "End of Program." << std::endl;
    
    return 0;
}