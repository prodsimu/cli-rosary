#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;
using namespace this_thread;
using namespace chrono;


void clean_terminal() {
  for (int i = 0; i < 100; i++) {
    cout << endl;
  }
}


void choose_mysteries() {
  int choice;
  cout << "Quais mistérios você deseja meditar?\n";
  cout << "1 - Mistérios gozosos   (Segunda-feira e sábado)\n";
  cout << "2 - Mistérios dolorosos (terça-feira e sexta-feira)\n";
  cout << "3 - Mistérios gloriosos (quarta-feira e domingo)\n";
  cin >> choice;
}


struct prayer {
  string text;
  int quantity;
  int duration;
};


vector<prayer> choose_prayer() {
  vector<prayer> rosary;

  ifstream archive("prayer.txt");
  
  string line, block;

  while (getline(archive, line)) {
    if (line == "---") {

      size_t slash = block.rfind('|');
      size_t slash2 = block.rfind('|', slash - 1);
      string texto = block.substr(0, slash2);

      int qty = stoi(block.substr(slash2 + 1, slash - slash2 - 1));
      int dur = stoi(block.substr(slash + 1));

      rosary.push_back({texto, qty, dur});
      block.clear();

    } else {
      block += line + "\n";
    }
  }

  if (!block.empty()) {
    size_t slash = block.rfind('|');
    size_t slash2 = block.rfind('|', slash - 1);
    string text = block.substr(0, slash2);

    int qtd = stoi(block.substr(slash2 + 1, slash - slash2 - 1));
    int dur = stoi(block.substr(slash + 1));
    
    rosary.push_back({text, qtd, dur});
  }
  return rosary;
}


void pray(vector<prayer> rosary = choose_prayer()) {
  for (const auto& o : rosary) {
    for(int i = 0; i < o.quantity; i++) {
      clean_terminal();
      cout << "---------------" <<  i + 1 << "x---------------\n" << o.text << endl;
      sleep_for(seconds(o.duration));
    }
  }
}


int main(){
  pray();
  return 0;
}
