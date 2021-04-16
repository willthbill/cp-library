// Cheatsheet til c++ indbyggede datastrukturer
  // af William Bille Meyling
  // når der bruges {kode} er det for at oprette et nyt scope og tillade folding i diverse editors
#include<bits/stdc++.h> // importerer hele c++ standard biblioteket
using namespace std; // gør at vi eks. kan skrive vector istedet for std::vector

// til ordered_set og ordered_map
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T1, typename T2>
using ordered_map = tree<T1, T2, less<T1>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
  // overblik over datastrukturer (https://en.cppreference.com/w/cpp/container)
    {
      // sekvenser
        // array: wrapper til c arrays
        // vector: dynamisk tabel (dvs. en array hvor man kan tilføje elementer i konstant tid)
        // deque: en blanding af en kø og en vector
        // forward_list: enkelt hægted liste (a -> b -> c)
        // list: dobbelt hægtet liste: (a <-> b <-> c)
      // sets
        // set: ordnet mængde, eks: (1,2,3)
        // unordered_set: hashset - ikke ordnet mængde, eks: (2,1,3)
        // multiset: samme som set men med mulighed for dubletter, eks: (1,2,2,3)
        // unordered_multiset: samme som unordered_set men med mulighed for dubletter, eks. (2,1,3,2)
        // ordered_set: samme som set men hvor man i log tid kan indexere eller finde positionen af et element
      // dictionaries (maps)
        // map: ordnet mængde af (key,value) par, eks: ((1,"a"),(2,"b"),(3,"c"))
        // unordered_map: hashamap - ikke ordnet mængde af (key,value) par, eks: ((2,"b"),(1,"a"),(3,"c"))
        // multimap: samme som map men med mulighed for dubletter af keys, eks: ((1,"a"),(2,"b"),(2,"d"),(3,"c"))
        // unordered_multimap: samme som unordered_map men med mulighed for dubletter, eks. ((2,"b"),(1,"a"),(3,"c"),(2,"d"))
        // ordered_map: samme som map men hvor man i log tid kan indexere eller finde positionen af en key
      // andet
        // queue: en kø (fifo)
        // stack: en stak (lifo)
        // priority_queue: en prioritetskø (man kan finde det største element hurtigt)
      // simple
        // pair: et par af værdier
        // tuple: generalisering af par
    }
  // std::vector<type> (https://en.cppreference.com/w/cpp/container/vector)
    {
      // oprettelse
        vector<int> a = {2,3,4}; // a = {2,6,4}
        vector<int> b (3); // b = {0,0,0}, vectoren sætter alle elementer til en default værdi
        vector<double> c; // c = {}
        vector<string> d (5, "ab"); // d = {"ab","ab","ab","ab", "ab"}, man kan give en værdi som vectoren bliver fyldt med
      // størrelsen
        cout << a.size() << " " << d.size() << endl; // "3 5"
      // tilføjelse af elementer
        a.push_back(5); // a = {2,3,4,5}
        a.insert(a.begin() + 1, 1); // a = {2,1,6,4,5}, OBS: insert er basalt set lineær i vector størrelsen
        assert(a == vector<int>({2,1,3,4,5}));
      // tilgå et element
        cout << a[2] << endl; // "6"
        cout << a.front() << endl; // a[0]
        cout << a.back() << endl; // a[a.size()-1]
      // ændre et element
        a[2] = 3;
      // iteration
        for(auto& e : a) cout << e << endl; // printer alle elementer
        for(int i = 0; i < a.size(); i++) cout << a[i] << endl; // printer alle elementer
        for(auto it = a.begin() + 1; it != a.end(); it++) cout << *it << endl; // printer alle elementer fra 1 til slut
        for(auto it = a.begin() + 1; it != a.begin() + 4; it++) cout << *it << endl; // printer alle elementer fra 1 til og med 3
        for(auto it = a.rbegin(); it != a.rend(); it++) cout << *it << endl; // printer alle elementer i omvendt rækkefølge
      // sortering
        sort(a.begin(),a.end()); // a = {1,2,3,4,5}, sortere i ikke-faldende rækkefølge
        sort(a.rbegin(),a.rend()); // a = {5,4,3,2,1}, sortere i ikke-stigende rækkefølge
        sort(a.begin(),a.end(),[](auto& e1, auto& e2) -> bool {
          return abs(e1-3) < abs(e2-3);
        }); // a = {3,4,2,5,1}, sorter efter afstanden til 3
        assert(a == vector<int>({3,4,2,5,1}));
      // fjernelse af elementer
        a.pop_back(); // a = {3,4,2,5}, fjerner sidste element
        assert(a == vector<int>({3,4,2,5}));
        a.erase(a.begin() + 2, a.end()); // a = {3,4}
        assert(a == vector<int>({3,4}));
        a.erase(a.begin() + 1); // a = {3}
        assert(a == vector<int>({3}));
        a.clear(); // a = {}, fjerner alle elementer
      // ændre størrelse
        a = {1,2,3};
        a.resize(7); // a = {1,2,3,0,0,0,0}
        assert(a == vector<int>({1,2,3,0,0,0,0}));
        a.resize(2); // a = {1,2}
        assert(a == vector<int>({1,2}));
      // sammenligning, brug ==, <=, <, >, >=
        if(a < b) cout << "a is lexicographically less than b" << endl;
        if(a == b) cout << "a is equal to b" << endl;
    }
  // 2d datastrukturer
    {
      // ved generiske datastrukturer (dvs. at man angiver typen i <type>) kan man skrive andre datastrukturer
      // eksempler:
        // map<set<int>,vector<int>>
        // unordered_set<vector<int>>
        // vector<queue<int>>
      // eksempel: 2d vector
        // oprettelse
          vector<vector<int>> a (2, vector<int> (3, 2)); // 2x3 matrix, a = {{2,2,2},{2,2,2}}
        // tilgå elemtent
          cout << a[1][2] << endl; // "2"
        // ændre element
          a[1][2] = 3;
        // iteration
          for(int i = 0; i < a.size(); i++) {
            for(int j = 0; j < a[i].size(); j++) cout << a[i][j] << endl;
          }
    }
  // std::pair<type1, type2> (https://en.cppreference.com/w/cpp/utility/pair)
    {
      // oprettelse
        pair<int,string> a = {3,"abc"};
        pair<double,pair<long long, long long>> b = make_pair(3.1415, make_pair(1,3)); // godt til explicit at angive at det er et pair da {} kan forvekles med vector eller andet
      // tilgå
        cout << a.first << " " << a.second << endl; // "3 abc"
      // sortering af vector med pairs
        // først sorteres efter pair.first derefter pair.second
        vector<pair<int,double>> v = {{3,2.0},{3,1.0},{2,10.0}};
        sort(v.begin(),v.end()); // {{2,10.0}, {3,1.0}, {3,2.0}};
        // assert
        auto v2 = vector<pair<int,double>>({make_pair(2,10.0), make_pair(3,1.0), make_pair(3,2.0)});
        assert(v == v2);
    }
  // std::queue<type> (https://en.cppreference.com/w/cpp/container/queue)
    {
      // oprettelse
        queue<int> q;
      // push
        q.push(1); // q = {1}
        q.push(3); // q = 1 -> 3
        q.push(2); // q = 1 -> 3 -> 2
      // tilgå elementer
        cout << q.front() << endl; // 1
        cout << q.back() << endl; // 2
      // størrelse
        cout << q.size() << endl; // "3"
        cout << q.empty() << endl; // false, "0"
      // pop (bruger fifo, first in first out)
        q.pop(); // q = {1 -> 3}
        q.pop(); // q = {1}
      // bfs med queue
        q = queue<int>();
        q.push(0);
        vector<vector<int>> adj = {{1}, {2,3}, {3}, {}};
        vector<bool> visited (4);
        while(!q.empty()) {
          int node = q.front(); q.pop();
          cout << "bfs node: " << node << endl;
          if(visited[node]) continue;
          visited[node] = true;
          for(int neighbour : adj[node]) q.push(neighbour);
        }
    }
  // std::stack<type> (https://en.cppreference.com/w/cpp/container/stack)
    {
      // oprettelse
        stack<int> s;
      // tilføjelse af værdier
        s.push(1); // s = {1}
        s.push(3); // s = {1 <- 3}
        s.push(2); // s = {1 <- 3 <- 2}
      // tilgå elementer
        cout << s.top() << endl; // "2"
      // størrelse
        cout << s.size() << endl; // "3"
        cout << s.empty() << endl; // "3"
      // fjernelse af elementer (bruger lifo, last in, first out)
        s.pop(); // s = {1 <- 3}
        s.pop(); // s = {1}
      // dfs med stack
        s = stack<int>();
        s.push(0);
        vector<vector<int>> adj = {{1}, {2,3}, {3}, {}};
        vector<bool> visited (4);
        while(!s.empty()) {
          int node = s.top(); s.pop();
          cout << "dfs node: " << node << endl;
          if(visited[node]) continue;
          visited[node] = true;
          for(int neighbour : adj[node]) s.push(neighbour);
        }
    }
  // deque<type> (https://en.cppreference.com/w/cpp/container/deque)
    {
      // en deque kan alt hvad en vector, queue og stack kan
      // alle operationer på nær insert er konstant tid **???
      // oprettelse
        deque<int> d;
      // tilføjelse af værdier
        d.push_back(3); // d = {1}
        d.push_front(2); // d = {2,1}
        d.insert(d.begin() + 1, 1); // d = {2,3,1}
        d.push_front(4); // d = {4,2,1,3}
        d.push_back(5); // d = {4,2,1,3,5}
        assert(d == deque<int>({4,2,1,3,5}));
      // tilgå elementer
        cout << d[1] << " " << d[4] << endl; // "2 5"
        cout << d.front() << endl; // "4"
        cout << d.back() << endl; // "5"
      // størrelse
        cout << d.size() << endl; // "5"
        cout << d.empty() << endl; // false, "0"
        d.resize(7); // d = {4,2,6,3,5,0,0}
        assert(d == deque<int>({4,2,1,3,5,0,0}));
        d.resize(4); // d = {4,2,6,3}
        assert(d == deque<int>({4,2,1,3}));
      // iteration: ligesom vector
      // ændring af elementer
        d[2] = 6; // d = {4,2,6,3}
      // fjernelse af elementer (bruger lifo, last in, first out)
        d.pop_back(); // d = {4,2,6}
        assert(d == deque<int>({4,2,6}));
        d.pop_front(); // d = {2,6}
        assert(d == deque<int>({2,6}));
        d.clear(); // d = {}
        assert(d == deque<int>());
    }
  // priority_queue<type, container, comparator> (https://en.cppreference.com/w/cpp/container/priority_queue)
    {
      // top er heletiden det største element i prioritetskøen
      // bemærk at prioritetskøen ikke nødvendigvis er sorteret
      {
        // oprettelse
          priority_queue<int> pq;
        // push (log(størrelse) tid)
          pq.push(1); // pq.top() er 1
          pq.push(3); // pq.top() er 3
          pq.push(2); // pq.top() er 3
          assert(pq.top() == 3);
        // tilgå elementer (konstant tid)
          cout << pq.top() << endl; // "3"
        // størrelse (konstant tid)
          cout << pq.size() << endl; // "3"
          cout << pq.empty() << endl; // false, "0"
        // pop (bruger fifo, first in first out), (log(størrelse) tid)
          pq.pop(); // pq.top() er 2
          pq.pop(); // pq.top() er 1
      }
      {
        // dijkstra med priority_queue
          priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq; // pq.top() er heletiden det mindste element
          pq.push({0,0}); // {weight, node}
          vector<vector<pair<int,int>>> adj = {{make_pair(3,1)}, {make_pair(1,2),make_pair(5,3)}, {make_pair(3,3)}, {}}; // an edge is {weight, neighbour}
          vector<int> distance (4, -1);
          while(!pq.empty()) {
            auto curr = pq.top(); pq.pop();
            cout << "dijkstra node, distance: " << curr.second << ", " << curr.first << endl;
            if(distance[curr.second] != -1) continue;
            distance[curr.second] = curr.first;
            for(auto edge : adj[curr.second]) pq.push({edge.first + curr.first, edge.second});
          }
          assert(distance == vector<int>({0,3,4,7}));
      }
      {
        // custom comparator
          auto compare = [](pair<int,int>& p1, pair<int,int>& p2) {
            return p1.first * p1.second < p2.first * p2.second;
          };
          priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(compare)> pq (compare); // pq.top() er heletiden elementet med størst produkt
          pq.push({2,3}); // pq.top() = {2,3}
          assert(pq.top() == make_pair(2,3));
          pq.push({5,4}); // pq.top() = {5,4}
          assert(pq.top() == make_pair(5,4));
          pq.push({1,2}); // pq.top() = {5,4}
          assert(pq.top() == make_pair(5,4));
      }
    }
  // set<type> og unordered_set<type> (https://en.cppreference.com/w/cpp/container/set)
    {
      // rækkefølgen vil heletiden være ikke-faldende for set, mens for unordered_set er rækkefølgen ikke garanteret
      // oprettelse
        set<int> s1;
        unordered_set<string> s2 = {"a","c","b"}; // for resten er s1 og s2 samme funktionalitet
      // tilføjelse af elementer
        // set er log(størrelse) tid mens unordered_set er konstant tid
        s1.insert(3); // s1 = {3}
        s1.insert(1); // s1 = {1,3}
        s1.insert(2); // s1 = {1,2,3}
        s1.insert(1); // s1 = {1,2,3}, kan ikke indeholde dubletter
      // check om key findes
        cout << (s1.count(3) > 0) << endl; // true, 1
        cout << (s1.count(5) > 0) << endl; // false, 0
      // størrelse
        cout << s1.size() << endl;
      // iteration: ligesom vector, lineær i størrelsen
        for(int e : s1) cout << e << endl;
      // fjerne elementer
        // set er log(størrelse) tid mens unordered_set er konstant tid
        s1.erase(s1.find(3)); // s1 = {1,2}
        s1.clear(); // s1 = {}
    }
  // map<keytype,valuetype> og unordered_map<keytype,valuetype> (https://en.cppreference.com/w/cpp/container/map)
    {
      // rækkefølgen vil heletiden være ikke-faldende (ift. key) for map, mens for unordered_map er rækkefølgen ikke garanteret
      // oprettelse
        map<int,string> mp1 = {{2,"b"}};
        unordered_map<string,double> mp2 = {{"b", 3.5}}; // for resten er mp1 og mp2 samme funktionalitet
      // tilføjelse af elementer
        // map er log(størrelse) tid mens unordered_map er konstant tid
        mp1[1] = "a";
        mp1[3] = "c";
      // check om key findes
        cout << (mp1.count(3) > 0) << endl; // true, 1
        cout << (mp1.count(5) > 0) << endl; // false, 0
      // tilgå elementer
        // map er log(størrelse) tid mens unordered_map er konstant tid
        cout << mp1[3] << endl;
      // størrelse
        cout << mp1.size() << endl;
      // iteration: ligesom vector hvor man iterere over pair<key,value>, lineær i størrelsen
        for(pair<int,string> p : mp1) cout << p.first << " " << p.second << endl;
      // fjerne elementer
        // map er log(størrelse) tid mens unordered_map er konstant tid
        mp1.erase(mp1.find(3)); // mp1 indeholder nu kun nøglen 1
        mp1.clear(); // mp1 er nu tom
    }
  // multiset<type> (https://en.cppreference.com/w/cpp/container/multiset)
    {
      // præcis samme som set bortset fra at multiset godt kan indeholde dubletter
      multiset<int> ms = {2,1,1,3}; // ms = {2,1,1,3}
      // når man skal slette et element kan give ms.find(value) en iterator der ikke nødvendigvis er den første value
    }
  // multimap<keytype,valuetype> (https://en.cppreference.com/w/cpp/container/multimap)
    {
      // præcis samme som map bortset fra at multimap godt kan indeholde dubletter
      multimap<int,string> mp = {{1,"a"}, {1,"b"}, {2,"c"}};
      // når man skal slette et element kan give ms.find(value) en iterator der ikke nødvendigvis er den første value
    }
  // ordered_set<type> og ordered_map<keytype,valuetype>
    {
      // OBS: de første linjer i dokumentet skal skrives i koden (l. 7-14)
      // ordered_set kan det samme som set plus følgende
        ordered_set<int> oset; // kan vist ikke initialiseres med {}
        oset.insert(4);
        oset.insert(1);
        oset.insert(7);
        oset.insert(5);
        cout << *oset.find_by_order(1) << endl; // "4", log(størrelse) tid, giver det 1'te element i ordered_set, giver default værdien for type hvis det er out of range
        cout << *oset.find_by_order(0) << endl; // "1"
        cout << *oset.find_by_order(3) << endl; // "7"
        assert(*oset.find_by_order(1) == 4);
        assert(*oset.find_by_order(0) == 1);
        assert(*oset.find_by_order(3) == 7);
        cout << oset.order_of_key(5) << endl; // "2", log(størrelse) tid, giver 'indexet' for elementet med nøglen 1
        cout << oset.order_of_key(5) << endl;
      // ordered_map er ligesom ordered_set bare hvor elementer sættes på følgende måde
        ordered_map<int,string> omap; // kan vist ikke initialiseres med {}
        omap[3] = "b";
        omap[1] = "a";
        auto p = *omap.find_by_order(1);
        cout << p.first << " " << p.second << endl; // "3 b"
        assert(p.first == 3 && p.second == "b");
        cout << omap.order_of_key(1) << endl; // "0"
        assert(omap.order_of_key(1) == 0);
    }
  // binary search på datastrukturer (https://en.cppreference.com/w/cpp/algorithm)
    {
      // lower_bound
      {
        // at finde det første element der ikke er mindre end en given værdi
        // kan bruges på vector (skal være sorteret), deque (skal være sorteret), set, map, multiset, multimap, orderet_set, ordered_map
        vector<int> container = {1,2,4,4,5};
        cout << *lower_bound(container.begin(), container.end(), 3) << endl; // 4
        cout << *lower_bound(container.begin(), container.end(), 4) << endl; // den første 4*/
        int index = lower_bound(container.begin(), container.end(), 4) - container.begin(); // giver indexet for 4, "2"
        assert(index == 2);
      }
      // upper_bound
      {
        // at finde det første element der er større end en given værdi
        // kan bruges på vector (skal være sorteret), deque (skal være sorteret), set, map, multiset, multimap, orderet_set, ordered_map
        vector<int> container = {1,2,4,4,5};
        cout << *upper_bound(container.begin(), container.end(), 3) << endl; // "4"
        cout << *upper_bound(container.begin(), container.end(), 4) << endl; // "5"*/
        int index = upper_bound(container.begin(), container.end(), 4) - container.begin(); // giver indexet for 5, "4"
        assert(index == 4);
      }
      // equal_range
      {
        // at finde det intervallet af elementer med en given værdi
        // kan bruges på det samme som lower_bound og upper_bound, men er brugbar til vector (skal være sorteret), deque (skal være sorteret), multiset og multimap
        vector<int> container = {1,2,4,4,4,5};
        auto range = equal_range(container.begin(), container.end(), 4);
        int left = range.first - container.begin();
        int right = range.second - container.begin() - 1; // range.second er lige efter ens range
        cout << left << " " << right << endl; // "2 4" left index og right index
        assert(left == 2 && right == 4);
        // iteration
        for(auto it = range.first; it != range.second; it++) {
          cout << *it << endl;
        }
      }
    }
  // andre brugbare funktioner (https://en.cppreference.com/w/cpp/algorithm)
    {
      vector<int> a,b;
      vector<int> v = {1,2,3}; // v kunne også være andre typer
      swap(a,b); // a = b, b = a
      min_element(v.begin(), v.end()); // mindste element i rangen
      max_element(v.begin(), v.end()); // største element i rangen
      reverse(v.begin(), v.end()); // vender en range om, {3,2,1}
      random_shuffle(v.begin(), v.end()); // bytter tilfældigt rundt på elementerne i en range
      next_permutation(v.begin(), v.end()); // modificere v til at indeholde den 'næste permutation'
      iota(v.begin(),v.end(),0); //fylder ud med 0, 1, 2, 3 .., v = {0,1,2}
      accumulate(v.begin(), v.end(), 0); // summen af elementer i v
    }
}
