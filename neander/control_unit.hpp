  #include <vector>
  #include <iostream>

struct control_unit{
  
  bool sel;
  int sel_ula;
  int carga_ac;
  bool incrementa_pc;
  int carga_pc;
  
  void selecao(ULA ula,RDM rdm,REM rem,NZ nz,memoria mem,RI ri,PC pc,AC ac,MUX mux){
    if(opcode==0){//STA
    //ciclo de busca
      pc.pc = carga_pc;
      rem.adress = pc.pc;
      //funcao read
      pc.pc=pc.pc+1
      rdm.adress = ri.ri;
    //fim
    //ciclo ce execucao
      pc.pc = carga_pc;
      rem.adress = pc.pc;
      //funcao read
      pc.pc=pc.pc+1;
      rdm.adress = rem.adress;
      rdm.data = mem.dados[index];
      rdm.data = ac.ac;
      ac.ac = rdm.data;
      //funcao write

    }
    else if(opcode==1){

    }
    else if(opcode==2){
      
    }
    else if(opcode==3){
      
    }
    else if(opcode==4){
      
    }
    else if(opcode==5){
      
    }
    else if(opcode==6){
      
    }
    else if(opcode==7){
      
    }
    else if(opcode==8){
      
    }
    else if(opcode==9){
      
    }
    else if(opcode==10){
      
    }
    else if(opcode==11){
      
    }
  }
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