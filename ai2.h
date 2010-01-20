#ifndef AI2_H
#define AI2_H

#include "defines.h"

class AgImo
{
  public:
    AgImo() {}
    ~AgImo() {}

  protected:
    int count_value(GARRAY pole, int x, int y, int p, int &c, int &k, int &s);

    int doprava(GARRAY pole, int x, int y, int p);
    int doleva(GARRAY pole, int x, int y, int p);
    int nahoru(GARRAY pole, int x, int y, int p);
    int dolu(GARRAY pole, int x, int y, int p);
    int vlevonahoru(GARRAY pole, int x, int y, int p);
    int vpravonahoru(GARRAY pole, int x, int y, int p);
    int vlevodolu(GARRAY pole, int x, int y, int p);
    int vpravodolu(GARRAY pole, int x, int y, int p);

    int check_cell(GARRAY papir, int x, int y, int w);
    coord check_array(GARRAY papir, int me, int difficulty);
};


// ai2:
//

class ai2 : public AgImo
{
    public:
        ai2();
        virtual ~ai2();
        coord play(GARRAY &game_board, int symbol, int difficulty);
    protected:
    private:
};

#endif // AI2_H
