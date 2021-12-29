
# Semestrální práce

- Program hledá nejkratší cesty mezi několika body ve grafe. (Body zadaný v určitém poradí).

- Program se spustit z příkazové řádky.
Napřiklad: ./cmake-build-release/semestalni_prace_pjc maps/map03.in --one_thread --multi_thread

- Pomoci přepínačů help a taky když nemá žadny argument, program vypíše:

  "Usage semestalni_prace_pjc:
  semestalni_prace_pjc <map file> [--one_thread] [--multi_thread] [--help]
  --one_thread: For single thread mode
  --multi_thread: For multiple thread mode
  --help: For help

- Program používá data ze souborů map01.in, map02.in, map03.in, případné i jiného,
   Data v souborech jenom čisla
   První řádek: 1 širka, 2 výská,  3 množství pointu, 4 množství překážek.
   Druchý řádek a ostatní: páry x a y pointu, a pak překážek.

- Program se da spustit v jednom thready nebo vice.
  Při spustení s argumenty [--one_thread] [--multi_thread] najednou, na konce vypíše čas potřebný pro oba mody.

- Výsledky běhu programu a naměřené časy při porovnání jedno- / více- vláknové verze

    map01.in 15x15: 12 ms/7ms
    map02.in 30x15: 40 ms/14ms
    map02.in 30x30: 32 ms/16ms