#include "gtest/gtest.h"
#include "../ArbreBinaire.h"
#include <sstream>

TEST(ArbreBinaire, ConstructeurNoThrow) {
  EXPECT_NO_THROW( ArbreBinaire<int> b ) ; 
}

TEST(ArbreBinaire, ConstructeurVideAssigneNullptr) {
  ArbreBinaire<int> b ; 
  EXPECT_TRUE(b.estVide ()) ; 
}

TEST(ArbreBinaire, insererUneValeurIterer) {
  ArbreBinaire<int> b ; 
  std::ostringstream os ; 
  b.inserer(1) ; 
  for (ArbreBinaire<int>::const_iterator it = b.cdebut (); it != b.cfin (); ++it) {
      os << *it ; 
    }
  EXPECT_EQ("1", os.str()) ; 
}

TEST(ArbreBinaire, InsererUneValeurVisiterEnOrdre) {
  ArbreBinaire<int> b ; 
  std::vector<int> attendu {1} ; 
  b.inserer(1) ; 
  EXPECT_EQ(attendu, b.visiteEnOrdre ()) ; 
}

TEST(ArbreBinaire, InsererTroisValeursVisiterEnOrdre) {
  ArbreBinaire<int> b ; 
  std::vector<int> attendu {1, 2, 3} ; 
  b.inserer(2) ; 
  b.inserer(1) ; 
  b.inserer(3) ; 
  EXPECT_EQ( attendu, b.visiteEnOrdre () ) ; 
}

TEST(ArbreBinaire, InsererSeptValeursVisiterEnOrdre) {
  ArbreBinaire<int> b ; 
  std::vector<int> attendu {1, 2, 3, 4, 5, 6, 7} ; 
  b.inserer(4) ; 
  b.inserer(2) ; 
  b.inserer(6) ; 
  b.inserer(1) ; 
  b.inserer(3) ; 
  b.inserer(5) ; 
  b.inserer(7) ; 
  EXPECT_EQ(attendu, b.visiteEnOrdre ()) ; 
}

class ArbreBinaireTest : public ::testing::Test {
public:
  ArbreBinaireTest() : arbre() {
    arbre.inserer(5) ; 
    arbre.inserer(3) ; 
    arbre.inserer(7) ; 
    arbre.inserer(2) ; 
    arbre.inserer(4) ; 
    arbre.inserer(6) ; 
    arbre.inserer(8) ; 
  }
  
  ArbreBinaire<int> arbre ; 
};

TEST_F(ArbreBinaireTest, chercherValeurPresente) {
  ArbreBinaire<int>::const_iterator it = arbre.chercher(6) ; 
  EXPECT_EQ(6, *it) ; 
}

TEST_F(ArbreBinaireTest, chercherValeurAbsente) {
  ArbreBinaire<int>::const_iterator it = arbre.chercher(25) ; 
  EXPECT_EQ(arbre.cfin (), it) ; 
}

TEST_F(ArbreBinaireTest, estSimilaireALuiMeme) {
  EXPECT_TRUE(arbre.estSimilaireA (arbre)) ; 
}

TEST_F(ArbreBinaireTest, estSimilaireFaux) {
  ArbreBinaire<int> autre ; 
  autre.inserer(12) ; 
  autre.inserer(24) ; 
  autre.inserer(6) ; 
  autre.inserer(0) ; 
  EXPECT_FALSE(arbre.estSimilaireA(autre)) ; 
}

TEST_F(ArbreBinaireTest, constructeurCopie) {
  ArbreBinaire<int> copie(arbre) ; 
  EXPECT_TRUE(arbre.estSimilaireA(copie)) ; 
}

TEST_F(ArbreBinaireTest, operateurAffectation) {
  ArbreBinaire<int> autre, vide ; 
  EXPECT_FALSE(arbre.estSimilaireA(autre)) ; 
  autre = arbre ; 
  EXPECT_TRUE(arbre.estSimilaireA(autre)) ; 
  arbre = vide ; 
  EXPECT_TRUE(arbre.estVide ()) ; 
}