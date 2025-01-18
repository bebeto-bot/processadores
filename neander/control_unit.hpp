  #include <array>
  #include <iostream>
  #include <cstdint>
struct control_unit{
  
  bool sel;
  std::uint8_t sel_ula;
  bool carga_ac;
  bool incrementa_pc;
  bool carga_pc;
  
  void busca(ULA ula,RDM rdm,REM rem,NZ nz,memoria mem,RI ri,PC pc,AC ac,MUX mux){
    
        
        rem.adress = pc.pc;
        rdm.dado = mem.read(rem.adress);  // Read memory
        pc.pc = pc.pc + 1;
        ri.ri=rdm.dado;
        
        
  }
  void selecao(ULA ula,RDM rdm,REM rem,NZ nz,memoria mem,RI ri,PC pc,AC ac,MUX mux){
    if(ri.ri==0){//STA
        // ciclo de execução (execution cycle)
        ac.ac = rdm.dado;  // Store value from memory to AC
        rem.adress = pc.pc;
        
        // Write back
        mem.memory[rem.adress] = ac.ac;

    }
    else if(ri.ri==1){

    }
    else if(ri.ri==2){
      
    }
    else if(ri.ri==3){
      
    }
    else if(ri.ri==4){
      
    }
    else if(ri.ri==5){
      
    }
    else if(ri.ri==6){
      
    }
    else if(ri.ri==7){
      
    }
    else if(ri.ri==8){
      
    }
    else if(ri.ri==9){
      
    }
    else if(ri.ri==10){
      
    }
    else if(ri.ri==11){
      
    }
  }
};

struct ULA{
  
  std::uint8_t x;
  std::uint8_t y;
  
  void receber(RDM a,AC b){
    x = b.ac;
    y = a.dado;
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
    std::uint8_t result;
    
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
  std::uint8_t adress;
};

struct RDM {
  std::uint8_t dado;
};
struct memoria{
  std::array<std::uint8_t,256> memory;
  memoria(){
    
  }
  std::uint8_t read(std::uint8_t address) {
        
        return memory[address];
  }
};
struct RI {
    std::uint8_t ri;
};
struct PC {
    std::uint8_t pc;
    void receber(control_unit a){
    pc = a.carga_pc;
  }
};
struct AC {
    std::uint8_t ac;
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
      d.adress = b.dado;
    }
  }
};