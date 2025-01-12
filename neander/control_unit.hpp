  #include <vector>
  #include <iostream>
class ControlUnit {

  bool sel;
  int sel_ula;
  int carga_ac;
  bool incrementa_pc;
  int carga_pc
  
};
class ULA {
  int x;
  int y;
  void receber(rdm a,acumulador b){
    x = b;
    y = a;
  }
  void operation(NZ result,ControlUnit a) {
    if (a.sel_ula == 0) {

      result.result = x + y;
    }
    else if(a.sel_ula == 1){
      result.result = x and y;
    }
    else if (a.sel_ula == 2){
      result.result = x or y;
    }
    else if(a.sel_ula == 3){
      result.result = y;
    }
  };

  class NZ {

    bool N;
    bool Z;
    int result;
    
    void operation(ControlUnit AC) {

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
  };

class REM {
  int adress;
};

class RDM {
  int data;
  int adress;
};
class memoria{
  std::vector<int> dados;
  std::vector<int> endereços;
};
class RI {
    int ri;
};
class PC {
    int pc;
    void receber(ControlUnit a){
    pc = a.carga_pc;
    
  }
};
class AC {
    int ac;
    void receber(ControlUnit a){
    ac = a.carga_ac;
    
  }
};
class MUX{
  void mux(ControlUnit a,RDM b,PC c,REM d){
    if(a.sel == false){
      d.adress = c.pc;
    }
    else if(a.sel == true){
      d.adress = b.adress;
    }
  }
};