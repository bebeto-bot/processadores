class ULA {
  int x;
  int y;

  void operation(AC c) {
    if (sel_ULA == 0) {

      c = x + y;
    }
  };

  struct NZ {

    bool N;
    bool Z;

    int sum;
    void operation(int result) {

      if (result > 0) {
        N = false;
        Z = false;
      } else if (result < 0) {
      }
    }
  };
