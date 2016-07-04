String floatToString(float f){
  int parteInteira = f;
  int parteDecimal = (f*100)%100; // 100 para pegar duas casas
  String s = (String) parteInteira;
  s += ".";
  s += (String) parteDecimal;
  return s;
}
