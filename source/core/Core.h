#pragma once

#include <vector>

/**
 * Provides pre-main initailization and post-main termination.
 * This class was originally called Main.
 * TODO I am pretty sure this is not actually necessary
 *      Refactor and remove this later
 */
class Core
{
   public:
    using Initializer = void (*)();

    static void addInitializer(Initializer init);
    static void initialize();

    using Terminator = void (*)();

    static void addTerminator(Terminator term);
    static void terminate();

   private:
    static size_t& startObjects();
    static size_t& finalObjects();

    static std::vector<Initializer>& getInitializer();
    static std::vector<Terminator>& getTerminator();
};