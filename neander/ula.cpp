class ULA {
  int x;
  int y;
  void receber(rdm a,acumulador b){
    x = b;
    y = a;
  }
  void operation(NZ result) {
    if (sel_ULA == 0) {

      result = x + y;
    }
    else if(sel_ULA == 1){
      result = x and y;
    }
    else if (sel_ULA == 2){
      result = x or y;
    }
    else if(sel_ULA == 3){
      result = y;
    }
  };

  struct NZ {

    bool N;
    bool Z;
    int result;
    
    void operation(carga AC) {

      if (result > 0) {
        N = false;
        Z = false;
      } else if (result < 0) {
        N = true;
        Z = false;
      }
      else{
        N = false;
        Z = true;
      }
    }
  }
