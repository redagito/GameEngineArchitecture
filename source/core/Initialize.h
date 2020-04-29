#pragma once

/**
 * Macros for pre-main initialization registration through Core
 * Additionally requires implementation of CLASS_NAME::register()
 * and/or CLASS_NAME::terminate()
 */

#define INITIALIZE_DECLARE()          \
    static bool registerInitialize(); \
    static void initialize();

#define INITIALIZE_DEFINE(CLASS_NAME)                                 \
    static bool CLASS_NAME##_init = CLASS_NAME::registerInitialize(); \
    bool CLASS_NAME::registerInitialize()                             \
    {                                                                 \
        static bool initRegistered = false;                           \
        if (initRegistered)                                           \
            return true;                                              \
        Core::addInitializer(initialize);                             \
        initRegistered = true;                                        \
        return true;                                                  \
    }

#define TERMINATE_DECLARE()          \
    static bool registerTerminate(); \
    static void terminate();

#define TERMINATE_DEFINE(CLASS_NAME)                                 \
    static bool CLASS_NAME##_term = CLASS_NAME::registerTerminate(); \
    bool CLASS_NAME::registerTerminate()                             \
    {                                                                \
        static bool termRegistered = false;                          \
        if (termRegistered)                                          \
            return true;                                             \
        Core::addTerminator(terminate);                              \
        termRegistered = true;                                       \
        return true;                                                 \
    }