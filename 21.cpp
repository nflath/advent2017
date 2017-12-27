#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <fstream>


class Pattern {
public:
  std::vector<std::vector<bool> > data;

  std::string asstr(bool newline = true) const {
    std::stringstream result;
    for(auto r : data) {
      for(auto b : r) {
        result << (b ? "#" : ".");
      }
      if(newline) {
        result << std::endl;
      } else {

        result << '/';
      }
    }
    return result.str().substr(0,result.str().size()-1);
  }

  int count() const {
    int result = 0;
    for(char c : asstr()) {
      if(c == '#') result++;
    }
    return result;
  }

  Pattern(std::vector<std::vector<bool> > data): data(data) {}
  Pattern() {}

  Pattern rotate() {
    std::vector<std::vector<bool> > newdata;
    if(data.size() == 2) {
      // 1 2  -> 3 1
      // 3 4  -> 4 2
      newdata.push_back(std::vector<bool>({data[1][0], data[0][0]}));
      newdata.push_back(std::vector<bool>({data[1][1], data[0][1]}));
    } else if( data.size() == 3) {
      // 1 2 3      7 4 1
      // 4 5 6  ->  8 5 2
      // 7 8 9  ->  9 6 3
      newdata.push_back(std::vector<bool>({data[2][0], data[1][0], data[0][0]}));
      newdata.push_back(std::vector<bool>({data[2][1], data[1][1], data[0][1]}));
      newdata.push_back(std::vector<bool>({data[2][2], data[1][2], data[0][2]}));
    }
    return Pattern(newdata);
  }

  Pattern flip_vertical() {
    std::vector<std::vector<bool> > newdata;
    for(int i = 0; i < data.size(); ++i) {
      std::vector<bool> r;
      for(int j =0 ; j < data.size(); ++j) {
        r.push_back(data[data.size()-1-i][j]);
      }
      newdata.push_back(r);
    }
    return Pattern(newdata);
  }

  Pattern flip_horizontal() {
    std::vector<std::vector<bool> > newdata;
    for(int i = 0; i < data.size(); ++i) {
      std::vector<bool> r;
      for(int j =0 ; j < data.size(); ++j) {
        r.push_back(data[i][data.size()-1-j]);
      }
      newdata.push_back(r);
    }
    return Pattern(newdata);
  }

};

std::map<Pattern, Pattern> original;


bool operator<(const Pattern& t, const Pattern& other) {
    return t.asstr() < other.asstr();
}
bool operator==(const Pattern& t, const Pattern& other) {
    return t.asstr() == other.asstr();
}

class Grid {
public:
  Pattern data;
  std::vector<std::vector<Grid* >> children;

  std::map<Pattern, std::vector<std::vector<Pattern>>>* map;

  Grid(Pattern data, std::map<Pattern, std::vector<std::vector<Pattern>>>* map): data(data), map(map) {
  }


  void advance() {

    if(!children.empty()) {
      if(children.size() == 2 && children[0][0]->data.data.size() == 3) {
        //Consolidate first! We


        std::vector<std::vector<Grid*>> new_children;
        std::vector<Grid*> row;

        std::vector<std::vector<bool>> b;
        b.push_back(std::vector<bool>({
              children[0][0]->data.data[0][0],children[0][0]->data.data[0][1]}));
        b.push_back(std::vector<bool>({
              children[0][0]->data.data[1][0],children[0][0]->data.data[1][1]}));
        row.push_back(new Grid(Pattern(b), map));
        b.clear();

        b.push_back(std::vector<bool>({
              children[0][0]->data.data[0][2],children[0][1]->data.data[0][0]}));
        b.push_back(std::vector<bool>({
              children[0][0]->data.data[1][2],children[0][1]->data.data[1][0]}));
        row.push_back(new Grid(Pattern(b), map));
        b.clear();

        b.push_back(std::vector<bool>({
              children[0][1]->data.data[0][1],children[0][1]->data.data[0][2]}));
        b.push_back(std::vector<bool>({
              children[0][1]->data.data[1][1],children[0][1]->data.data[1][2]}));
        row.push_back(new Grid(Pattern(b), map));
        b.clear();

        new_children.push_back(row);
        row.clear();

        b.push_back(std::vector<bool>({
              children[0][0]->data.data[2][0],children[0][0]->data.data[2][1]}));
        b.push_back(std::vector<bool>({
              children[1][0]->data.data[0][0],children[1][0]->data.data[0][1]}));
        row.push_back(new Grid(Pattern(b), map));
        b.clear();

        b.push_back(std::vector<bool>({
              children[0][0]->data.data[2][2],children[0][1]->data.data[2][0]}));
        b.push_back(std::vector<bool>({
              children[1][0]->data.data[0][2],children[1][1]->data.data[0][0]}));
        row.push_back(new Grid(Pattern(b), map));
        b.clear();
        b.push_back(std::vector<bool>({
              children[0][1]->data.data[2][1],children[0][1]->data.data[2][2]}));
        b.push_back(std::vector<bool>({
              children[1][1]->data.data[0][1],children[1][1]->data.data[0][2]}));
        row.push_back(new Grid(Pattern(b), map));
        b.clear();
        new_children.push_back(row);row.clear();



        b.push_back(std::vector<bool>({
              children[1][0]->data.data[1][0],children[1][0]->data.data[1][1]}));
        b.push_back(std::vector<bool>({
              children[1][0]->data.data[2][0],children[1][0]->data.data[2][1]}));
        row.push_back(new Grid(Pattern(b), map));
        b.clear();
        b.push_back(std::vector<bool>({
              children[1][0]->data.data[1][2],children[1][1]->data.data[1][0]}));
        b.push_back(std::vector<bool>({
              children[1][0]->data.data[2][2],children[1][1]->data.data[2][0]}));
        row.push_back(new Grid(Pattern(b), map));
        b.clear();


        b.push_back(std::vector<bool>({
              children[1][1]->data.data[1][1],children[1][1]->data.data[1][2]}));
        b.push_back(std::vector<bool>({
              children[1][1]->data.data[2][1],children[1][1]->data.data[2][2]}));

        row.push_back(new Grid(Pattern(b), map));
        new_children.push_back(row);

        children = new_children;


      }
      //std::cout << std::endl;

      for(auto r : children) {
        for(auto c : r) {
          c->advance();
        }
      }
    } else {
      std::vector<std::vector<Pattern>> new_children = (*map)[data];
      //std::cout << data.asstr(false) << " -> " << original[data].asstr(false) <<  " : ";

      if(new_children.size() == 1) {
        data = new_children[0][0];
        return;
      }
      for(auto r : new_children) {
        std::vector<Grid*> row;
        for(auto p : r) {
          row.push_back(new Grid(p,map));
          //std::cout << p.asstr(false) << '\t' ;
        }
        data = Pattern(std::vector<std::vector<bool>>());
        children.push_back(row);
      }
      //std::cout << std::endl;

    }
  }

  int count() const {
    int result = 0;
    if(children.size()) {
      for(const auto& r : children) {
        for(const auto& c : r) {
          result += c->count();
        }
      }
      return result;
    }
    return data.count();
  }
};

// .#.
// ..#
// ###
int main() {
  std::vector<std::vector<bool> > base({{false, true, false},
        {false, false, true},
          {true, true, true}});

  Pattern base_pattern(base);

  std::ifstream infile("day21input");

  std::string line;
  std::map<Pattern, std::vector<std::vector<Pattern>>> map;

  while(std::getline(infile, line)) {
    std::stringstream ss(line);
    char c;

    //std::cout << line << std::endl;
    std::vector<std::vector<bool>> p;
    std::vector<bool> tmp;
    while(ss >> c) {
      //std::cout << ' ' << c << ' ' << std::endl;
      if(c == '.') tmp.push_back(false);
      else if(c == '#') tmp.push_back(true);
      else if(c == '/') {
        p.push_back(tmp);
        tmp.clear();
      } else if( c == '=') {
        break;
      }
    }
    p.push_back(tmp);
    tmp.clear();
    //    std::cout << Pattern(p).asstr() << std::endl;

    ss >> c;// >> c >> c;
    std::vector<std::vector<bool>> r;
    while(ss >> c) {
      if(c == '.') tmp.push_back(false);
      else if(c == '#') tmp.push_back(true);
      else if(c == '/') {
        r.push_back(tmp);
        tmp.clear();
      }
    }
    r.push_back(tmp);
    std::vector<std::vector<Pattern>> replacements;
    Pattern pattern(p);
    if(r.size() == 4) {
      // split r up
      std::vector<Pattern> row;
      row.push_back(Pattern({{r[0][0],r[0][1]},{r[1][0],r[1][1]}}));
      row.push_back(Pattern({{r[0][2],r[0][3]},{r[1][2],r[1][3]}}));
      replacements.push_back(row);
      row.clear();
      row.push_back(Pattern({{r[2][0],r[2][1]},{r[3][0],r[3][1]}}));
      row.push_back(Pattern({{r[2][2],r[2][3]},{r[3][2],r[3][3]}}));
      replacements.push_back(row);
    } else {
      replacements.push_back({Pattern(r)});
    }


    Pattern o = pattern;
    for(int i = 0; i < 4; ++i) {
      //std::cout << pattern.asstr() << std::endl << std::endl;
      if(map.find(pattern) != map.end()) {
        if(map[pattern] != replacements) {
          //std::cout << "ERROR: " << original[pattern].asstr(false) << " vs " << pattern.asstr(false);
        }
      }
      map[pattern] = replacements;
      map[pattern.flip_horizontal()] = replacements;
      map[pattern.flip_vertical()] = replacements;

      original[pattern] = o;
      original[pattern.flip_horizontal()] = o;
      original[pattern.flip_vertical()] = o;

      pattern = pattern.rotate();
    }
  }

  // std::cout << base_pattern.asstr() << std::endl;
  // std::cout << base_pattern.rotate().asstr() << std::endl;
  // std::cout << base_pattern.rotate().rotate().asstr() << std::endl;
  // std::cout << base_pattern.rotate().rotate().rotate().asstr() << std::endl;
  Grid g(base, &map);
  std::cout << g.count() << std::endl;
  for(int i = 0; i < 18; ++i) {
    std::cout << std::endl << "Advancing: " << i << std::endl;
    g.advance();
  }
  std::cout << g.count() << std::endl;
  // 117 too low
  // 120 too low
}
