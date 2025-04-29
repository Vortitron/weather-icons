#ifndef WEATHER_ANIMATIONS_ANIMATED_ICONS_H
#define WEATHER_ANIMATIONS_ANIMATED_ICONS_H

#include <Arduino.h>

// Generated animated bitmap data for weather icons
// Original icons from https://github.com/basmilius/weather-icons

// Animated icon mapping structure
struct AnimatedIconMapping {
    const char* condition;
    const char* variant; // 'day', 'night', or empty string
    const uint8_t** frames;
    uint8_t frameCount;
    uint16_t frameDelay; // ms between frames
};

const AnimatedIconMapping animatedWeatherIcons[] = {
    {NULL, NULL, NULL, 0, 0} // End marker
};

// Helper function to find animated icon by condition and time of day
const AnimatedIconMapping* findAnimatedWeatherIcon(const char* condition, bool isDay) {
    const char* variant = isDay ? "day" : "night";
    
    // First try to find exact match with day/night variant
    for (size_t i = 0; animatedWeatherIcons[i].condition != NULL; i++) {
        if (strcmp(animatedWeatherIcons[i].condition, condition) == 0) {
            // If this condition has a day/night variant, match it
            if (animatedWeatherIcons[i].variant[0] != '\0') {
                if (strcmp(animatedWeatherIcons[i].variant, variant) == 0) {
                    return &animatedWeatherIcons[i];
                }
            } else {
                // For conditions without day/night variants, return the first match
                return &animatedWeatherIcons[i];
            }
        }
    }
    
    // If no exact match with variant, return any match with the condition
    for (size_t i = 0; animatedWeatherIcons[i].condition != NULL; i++) {
        if (strcmp(animatedWeatherIcons[i].condition, condition) == 0) {
            return &animatedWeatherIcons[i];
        }
    }
    
    // Fallback to cloudy if no match
    for (size_t i = 0; animatedWeatherIcons[i].condition != NULL; i++) {
        if (strcmp(animatedWeatherIcons[i].condition, "cloudy") == 0) {
            return &animatedWeatherIcons[i];
        }
    }
    
    // If all else fails, return the first icon
    return &animatedWeatherIcons[0];
}
#endif // WEATHER_ANIMATIONS_ANIMATED_ICONS_H
