#include "Mixer.h"

#include <iostream>
#include <SDL_mixer.h>

#include "Music.h"
#include "Sound.h"

void Mixer::Init()
{
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048) < 0)
    {
        throw std::runtime_error(std::string("Failed to init SDL_Mixer : ") + Mix_GetError());
    }
}

void Mixer::Destroy()
{
    Mix_Quit();
}

void Mixer::Play(const Music& music)
{
    Mix_PlayMusic(music.GetHandle(), -1);
}

void Mixer::Play(const Sound& sound)
{
    Mix_PlayChannel(-1, sound.GetHandle(), 0);
}
