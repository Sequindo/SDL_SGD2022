#ifndef game_misc_hpp
#define game_misc_hpp

namespace GameConstants {
    inline const char* title {"Untitled Cow Gore Game"};
    inline const uint32_t width = 1366;
    inline const uint32_t height = 768;

    // Player - related constants
    inline const uint32_t playerFrameH = 512;
    inline const uint32_t playerFrameW = 720;
    inline const uint32_t playerEntityH = 128;
    inline const uint32_t playerEntityW = 180;

    // Slaughterhouse flooring - related constants
    inline const uint32_t floorFrameSquare = 860;
    inline const uint32_t floorEntitySquare = 86;

    // Animation - related stuff
    inline const uint32_t maxTimeBetweenAnimationRefresh = 100u;
    inline const uint32_t minTimeBetweenAnimationRefresh = 1u;
    inline const uint32_t animationFreqStep = 16u;

    // Physics - related stuff
    inline const double playerAcceleration = 5u;
}

#endif