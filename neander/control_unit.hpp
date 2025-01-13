  #include <vector>
  #include <iostream>

struct control_unit{
  
  bool sel;
  int sel_ula;
  int carga_ac;
  bool incrementa_pc;
  int carga_pc
  
  
};

struct ULA{
  
  int x;
  int y;
  
  void receber(RDM a,AC b){
    x = b.ac;
    y = a.data;
  }
  void operation(NZ result,control_unit a) {
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
  }
  };

struct NZ {
    
    bool N;
    bool Z;
    int result;
    
    void operation(control_unit a) {

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

struct REM {
  int adress;
};

struct RDM {
  int data;
  int adress;
};
struct memoria{
  std::vector<int> dados;
  std::vector<int> endereços;
};
struct RI {
    int ri;
};
struct PC {
    int pc;
    void receber(control_unit a){
    pc = a.carga_pc;
  }
};
struct AC {
    int ac;
    void receber(control_unit a){
    ac = a.carga_ac;
  }
};
struct MUX{
  void mux(control_unit a,RDM b,PC c,REM d){
    if(a.sel == false){
      d.adress = c.pc;
    }
    else if(a.sel == true){
      d.adress = b.adress;
    }
  }
};