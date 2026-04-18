//
// Created by MashaGuzhva on 12/04/2026.
//

#ifndef PROJECT_SINGLEFILERUNNER_H
#define PROJECT_SINGLEFILERUNNER_H

// klasa odpowiedzialna za uruchomienie trybu single file
class SingleFileRunner {
public:
    // uruchamia cały tryb single file:
    // - wczytuje dane z pliku
    // - sortuje wybraną strukturę
    // - sprawdza poprawność sortowania
    // - zapisuje wynik do pliku wyjściowego
    static bool run();
};

#endif // PROJECT_SINGLEFILERUNNER_H