class tasks {
public:
  tasks();
  void doing() {
    if (mode != -1)
      switch (mode) {
        case 0:
          first();
        case 1:
          second();
        case 2:
          third();
        case 3:
          fourth();
        case 4:
          fifth();
        case 5:
          sixth();
        case 6:
          seventh();
        case 7:
          eighth();
        case 8:
          nineth();
        case 9:
          tenth();
      }
  }

  void first()
  {

  }

  void second()
  {

  }

  void third()
  {

  }

  void fourth()
  {

  }

  void fifth(){

  }

  void sixth()
  {

  }

  void seventh()
  {

  }

  void eighth()
  {

  }

  void nineth()
  {

  }

  void tenth()
  {

  }
private:
  int mode = -1;
};