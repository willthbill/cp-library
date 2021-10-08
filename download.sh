SCRIPT_DIR="$(dirname $(realpath ${BASH_SOURCE[0]}))"

DIR="$SCRIPT_DIR/resources"
rm -rf "$DIR"
mkdir -p "$DIR"

git clone https://github.com/ecnerwala/cp-book "$DIR/cp-book"
git clone https://github.com/kth-competitive-programming/kactl "$DIR/kactl"
git clone https://github.com/e-maxx-eng/e-maxx-eng.git "$DIR/cp-algorithms.com"
wget https://vlecomte.github.io/cp-geo.pdf --output-document "$DIR/cp-geo.pdf"
wget https://cses.fi/book/book.pdf --output-document "$DIR/csesbook.pdf"
