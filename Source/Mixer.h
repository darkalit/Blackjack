#pragma once

class Sound;
class Music;

class Mixer
{
public:
    Mixer() = delete;
    ~Mixer() = delete;

    static void Init();
    static void Destroy();

    static void Play(const Music& music);
    static void Play(const Sound& sound);
};

