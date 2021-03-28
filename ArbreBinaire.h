
/** 
 * @file   ArbreBinaire.h
 * @author Pascal Charpentier
 * @version 0.1
 *
 * Created on 16 mars 2021, 11:03
 */

#ifndef ARBREBINAIRE_H
#define ARBREBINAIRE_H

#include <queue>

template<typename TValeur>
class ArbreBinaire
{
private:

#include "noeud.h"

public:

#include "iterator.h"

public:

  /**
   * Constructeur par défaut: arbre vide
   */

  ArbreBinaire () : racine (nullptr) { }

  /**
   * Constructeur de copie
   * 
   * Utilise la visite par niveau
   * 
   * @param source Arbre à recopier
   */

  ArbreBinaire (const ArbreBinaire &source) : racine (nullptr)
  {
    if (!source.racine) return;

    std::queue<Noeud *> enAttente;
    Noeud *courant = source.racine;
    enAttente.push (courant);

    while (!enAttente.empty ())
      {
        courant = enAttente.front ();
        enAttente.pop ();
        if (courant->reqDroite ()) enAttente.push (courant->reqDroite ());
        if (courant->reqGauche ()) enAttente.push (courant->reqGauche ());
        inserer (courant->reqValeur ());
      }
  }

  /**
   * Destructeur: désalloue tous les noeuds
   */

  virtual
  ~ArbreBinaire ()
  {
    detruireLeSousArbre (racine);
  }

  /**
   * Opérateur d'affectation
   * @param autre Arbre à affecter à l'arbre courant
   * @return le membre de droite
   */
  const ArbreBinaire& operator= (ArbreBinaire autre)
  {
    Noeud *temp = this->racine;
    this->racine = autre.racine;
    autre.racine = temp;
    return (*this);
  }

  /**
   * Retourne le plus petit noeud de l'arbre courant
   * @return adresse du noeud le plus à gauche de l'arbre
   */

  Noeud *
  minimumArbre () const
  {
    if (!racine) return nullptr;
    return minimumDuSousArbre (racine);
  }

  /**
   * Recherche la valeur maximale de l'arbre courant
   * @return Adresse du noeud le plus à droite de l'arbre (contenant la valeur
   * max)
   */

  Noeud *
  maximumArbre () const
  {
    if (!racine) return nullptr;
    return maximumDuSousArbre (racine);
  }

  /**
   * Début d'une visite en ordre
   * @return itérateur constant pointant au début d'un arbre visité en ordre
   */

  inOrder_const_iterator
  enOrdreConstDebut () const
  {
    return inOrder_const_iterator (this, minimumArbre ());
  }

  /**
   * Début d'une visite préordre
   * @return itrateur constant pointant au début d'un arbre visité préordre
   */

  preOrdre_const_iterator
  preOrdreConstDebut () const
  {
    return preOrdre_const_iterator (this, racine);
  }

  /**
   * Début d'une visite en ordre, version non-const
   * @return itérateur non constant pointant au début d'un arbre visité en 
   * ordre
   */

  inOrder_iterator
  enOrdreDebut () const
  {
    return inOrder_iterator (this, minimumArbre ());
  }

  /**
   * Début d'une visite préordre, version non-const
   * @return itérateur non constant pointant au début d'un arbre visité 
   * préordre.
   */

  preOrdre_iterator
  preOrdreDebut () const
  {
    return preOrdre_iterator (this, racine);
  }

  /**
   * Fin d'une visite en ordre, const
   * @return Itérateur pointant à nullptr
   */

  inOrder_const_iterator
  enOrdreConstFin () const
  {
    return inOrder_const_iterator (this, nullptr);
  }

  /**
   * Fin d'une visite préordre
   * @return itérateur pointant à nullptr
   */

  preOrdre_const_iterator
  preOrdreConstFin () const
  {
    return preOrdre_const_iterator (this, nullptr);
  }

  /**
   * Fin d'une visite en ordre
   * @return itérateur pointant à nullptr
   */

  inOrder_iterator
  enOrdreFin () const
  {
    return inOrder_iterator (this, nullptr);
  }

  /**
   * Fin d'une visite préordre, version non const
   * @return itérateur à nullptr
   */

  preOrdre_iterator
  preOrdreFin () const
  {
    return preOrdre_iterator (this, nullptr);
  }

  /**
   * Visite l'arbre courant en postordre
   * @return vecteur contenant la liste des valeurs des noeuds visités dans 
   * l'ordre de la visite
   */

  std::vector<TValeur>
  visitePostOrdre () const
  {
    std::vector<TValeur> v;
    visitePostOrdreDansLeSousArbre (racine, v);
    return v;
  }

  /**
   * Visite l'arbre courant en préordre
   * @return vecteur contenant les valeurs visitées dans l'ordre de la visite
   */

  std::vector<TValeur>
  visitePreOrdre () const
  {
    std::vector<TValeur> v;
    visitePreOrdreDansLeSousArbre (racine, v);
    return v;
  }

  /**
   * Visite en ordre de l'arbre courant
   * @return vecteur contenant la liste des valeurs visitées.  Sera donc 
   * automatiquement triée.
   */

  std::vector<TValeur>
  visiteEnOrdre () const
  {
    std::vector<TValeur> v;
    visiteEnOrdreDansLeSousArbre (racine, v);
    return v;
  }

  /**
   * Recherche un élément dans l'arbre
   * @param valeur valeur à repérer dans l'arbre courant
   * @return un itérateur en-ordre pointant vers le noeud contenant la valeur
   * recherchée.  Sinon retourne un itérateur à fin.
   */

  inOrder_iterator
  chercher (const TValeur &valeur) const
  {
    return chercherDansLeSousArbre (valeur, racine);
  }

  /**
   * Insertion d'une valeur dans l'arbre courant
   * @param val valeur qui sera insérée dans l'arbre
   */

  void
  inserer (const TValeur &val)
  {
    Noeud *nouveauNoeud = new Noeud (val);
    if (estVide ()) racine = nouveauNoeud;
    else insererDansLeSousArbre (*nouveauNoeud, racine);
  }

  /**
   * Supprime une valeur de l'arbre courant. Garantit la préservation de la 
   * structure d'arbre binaire de recherche.
   * @param iter itérateur au noeud à supprimer
   */
  void
  supprimer (base_const_iterator iter)
  {
    Noeud *courant = iter.reqCourant ();
    if (!courant->reqGauche ()) transplanter (courant, courant->reqDroite ());
    else if (!courant->reqDroite ()) transplanter (courant, courant->reqGauche ());
    else
      {
        Noeud* succ = minimumDuSousArbre (courant->reqDroite ());
        if (!succ->estEnfantDe (*courant))
          {
            transplanter (succ, succ->reqDroite ());
            succ->asgEnfantDroite (courant->reqDroite ());
            succ->reqDroite ()->asgParent (*courant);
          }
        transplanter (courant, succ);
        succ->asgEnfantGauche (courant->reqGauche ());
        succ->reqGauche ()->asgParent (*courant);
      }
    delete courant;
  }

  /**
   * Vérifie si un sous arbre est vide
   * @param sousArbre adresse de la racine du sous-arbre à vérifier
   * @return true si le sous-arbre ne contient aucun élément
   */

  bool
  leSousArbreEstVide (Noeud *sousArbre) const
  {
    return !sousArbre;
  }

  /**
   * Vérifie si un arbre est vide
   * @return true si l'arbre courant est vide
   */

  bool
  estVide () const
  {
    return leSousArbreEstVide (racine);
  }

  /**
   * Vérifie que l'arbre courant a la même structure qu'un autre arbre
   * @param autre arbre comparé à l'arbre courant
   * @return true si les deux arbres ont la même structure
   */

  bool
  estSimilaireA (const ArbreBinaire &autre)
  {
    return lesSousArbresSontSimilaires (this->racine, autre.racine);
  }

private:

  /**
   * Compare la structure de deux sous-arbres
   * @param lhs sous-arbre à comparer
   * @param rhs autre sous-arbre à comparer
   * @return true si les deux sous-arbres ont la même structure
   */

  bool
  lesSousArbresSontSimilaires (const Noeud *lhs, const Noeud *rhs) const
  {
    if (!(lhs and rhs)) return (!(lhs or rhs));
    return lesSousArbresSontSimilaires (lhs->reqGauche (), rhs->reqGauche ()) and
            lesSousArbresSontSimilaires (lhs->reqDroite (), rhs->reqDroite ());
  }

  /**
   * Désalloue tous les noeuds d'un sous-arbre y-compris la racine
   * 
   * Utilise une visite par niveau
   * 
   * @param sousArbre Racine du sous-arbre à désallouer
   */

  void
  detruireLeSousArbre (Noeud *sousArbre)
  {
    if (!sousArbre) return;

    std::queue<Noeud *> enAttente;
    Noeud *courant = sousArbre;
    enAttente.push (courant);

    while (!enAttente.empty ())
      {
        courant = enAttente.front ();
        enAttente.pop ();
        if (courant->reqDroite ()) enAttente.push (courant->reqDroite ());
        if (courant->reqGauche ()) enAttente.push (courant->reqGauche ());
        delete courant;
      }
  }

  /**
   * Recherche un élément dans un sous-arbre
   * @param valeur valeur à repérer dans le sous-arbre
   * @param debut racine du sous-arbre où faire la recherche
   * @return un itérateur "en-ordre" pointant vers le noeud contenant la 
   * valeur cherchée, sinon un itérateur à fin.
   */

  inOrder_iterator
  chercherDansLeSousArbre (const TValeur &valeur, Noeud *debut) const
  {
    if (!debut) return enOrdreFin ();
    if (valeur == debut->reqValeur ()) return inOrder_iterator (this, debut);
    if (valeur < debut->reqValeur ()) return chercherDansLeSousArbre (valeur, debut->reqGauche ());
    return chercherDansLeSousArbre (valeur, debut->reqDroite ());
  }

  /**
   * Retourne le plus petit noeud d'un sous-arbre
   * @param depart adresse de la racine du sous-arbre
   * @return Adresse du noeud le plus à gauche (contenant la valeur min)
   */

  Noeud *
  minimumDuSousArbre (Noeud *depart) const
  {
    Noeud *courant = depart;
    while (courant->reqGauche ()) courant = courant->reqGauche ();
    return courant;
  }

  /**
   * Recherche la valeur maximale d'un sous-arbre
   * @param depart adresse de la racine du sous-arbre
   * @return adresse du noeud le plus à droite (contenant la valeur max)
   */

  Noeud *
  maximumDuSousArbre (Noeud *depart) const
  {
    Noeud *courant = depart;
    while (courant->reqDroite ()) courant = courant->reqDroite ();
    return courant;
  }

  /**
   * Vérifie qu'un noeud est à gauche de son parent
   * @param noeud adresse du noeud à tester
   * @return true si le noeud a un parent et que le noeud est enfant gauche
   * de ce parent
   */

  bool
  leNoeudEstUnEnfantDeGauche (Noeud *noeud)
  {
    if (!noeud->reqParent ()) return false;
    return ((noeud->reqParent ()->reqGauche ()) == noeud);
  }

  /**
   * Vérifie qu'un noeud est à droite de son parent
   * @param noeud adresse du noeud à tester
   * @return true si le noeud a un parent et que le noeud est enfant droite
   * de ce parent.
   */

  bool
  leNoeudEstUnEnfantDeDroite (Noeud *noeud)
  {
    if (!noeud->reqParent ()) return false;
    return ((noeud->reqParent ()->reqDroite ()) == noeud);
  }

  /**
   * Retourne le successeur d'un noeud lors d'une visite en ordre
   * @param courant adresse du noeud courant
   * @return adresse du noeud suivant pour la visite en ordre
   */

  Noeud *
  successeurEnOrdre (Noeud* courant) const
  {
    if (courant->reqDroite () != nullptr) return minimumDuSousArbre (courant->reqDroite ());
    Noeud *suivant = courant->reqParent ();
    while ((suivant != nullptr) and (courant == suivant->reqDroite ()))
      {
        courant = suivant;
        suivant = suivant->reqParent ();
      }
    return suivant;
  }

  /**
   * Retourne le successeur d'un noeud lors d'une visite préordre
   * @param courant adresse du noeud courant
   * @return adresse du noeud suivant pour la visite préordre
   */

  Noeud*
  successeurPreOrdre (Noeud* courant) const
  {
    if (courant->reqGauche ()) return courant->reqGauche ();
    Noeud* actuel = courant;
    Noeud* parent = courant->reqParent ();
    while ((parent != nullptr) and (parent->reqDroite () == actuel))
      {
        actuel = parent;
        parent = parent->reqParent ();
      }
    if (!parent) return nullptr;
    return parent->reqDroite ();
  }

  /**
   * Visite récursive postordre d'un sous-arbre
   * @param sousArbre adresse de la racine du sous-arbre à visiter
   * @param resultat vecteur contentant les valeurs visitées dans l'ordre
   * de la visite
   */

  void
  visitePostOrdreDansLeSousArbre (Noeud* sousArbre, std::vector<TValeur>& resultat) const
  {
    if (!sousArbre) return;
    visitePostOrdreDansLeSousArbre (sousArbre->reqGauche (), resultat);
    visitePostOrdreDansLeSousArbre (sousArbre->reqDroite (), resultat);
    resultat.push_back (sousArbre->reqValeur ());
  }

  /**
   * Visite un sous-arbre en préordre récursivement
   * @param sousArbre adresse de la racine du sous-arbre visité
   * @param resultat vecteur contenant les valeurs des noeuds visités dans 
   * l'ordre de la visite.
   */

  void
  visitePreOrdreDansLeSousArbre (Noeud* sousArbre, std::vector<TValeur>& resultat) const
  {
    if (!sousArbre) return;
    resultat.push_back (sousArbre->reqValeur ());
    visitePreOrdreDansLeSousArbre (sousArbre->reqGauche (), resultat);
    visitePreOrdreDansLeSousArbre (sousArbre->reqDroite (), resultat);
  }

  /**
   * Visite un sous-arbre en ordre, par récurrence
   * @param sousArbre adresse de la racine du sous-arbre à visiter
   * @param resultat vecteur contenant la liste des valeurs visitées dans
   * l'ordre de la visite
   */

  void
  visiteEnOrdreDansLeSousArbre (Noeud *sousArbre, std::vector<TValeur> &resultat) const
  {
    if (!sousArbre) return;
    visiteEnOrdreDansLeSousArbre (sousArbre->reqGauche (), resultat);
    resultat.push_back (sousArbre->reqValeur ());
    visiteEnOrdreDansLeSousArbre (sousArbre->reqDroite (), resultat);
  }

  /**
   * Insère un noeud comme enfant d'un autre noeud.  Est inséré automatiquement
   * à gauche ou à droite suivant sa valeur.
   * @param noeud référence au noeud à insérer
   * @param feuille adresse du noeud où faire l'insertion
   */

  void
  insererDansLaFeuille (Noeud &noeud, Noeud *feuille)
  {
    noeud.asgParent (*feuille);
    feuille->asgEnfant (noeud);
  }

  /**
   * Insertion récursive d'un noeud dans un sous-arbre
   * @param noeud nouveau noeud à insérer
   * @param sousArbre adresse de la racine du sous-arbre oû faire l'insertion
   */

  void
  insererDansLeSousArbre (Noeud &noeud, Noeud *sousArbre)
  {
    Noeud *destination = (noeud < *sousArbre) ? sousArbre->reqGauche () : sousArbre->reqDroite ();
    if (!destination) insererDansLaFeuille (noeud, sousArbre);
    else insererDansLeSousArbre (noeud, destination);
  }

  /**
   * Détache et désalloue un noeud d'un arbre.  ATTENTION c'est une opération
   *  risquée!!!  L'appelant est responsable de garantir que
   * le noeud à effacer n'a pas d'enfant alloué, ou que l'adresse des enfants
   * est conservée afin de pouvoir les libérer.
   * @param noeud adresse du noeud à effacer.
   */
  void
  effacerLeNoeud (Noeud *noeud)
  {
    Noeud *parent = noeud->reqParent ();
    parent->asgEnfantGauche (nullptr);
    parent->asgEnfantDroite (nullptr);
    delete noeud;
  }

  /**
   * Accroche un sous-arbre à une adresse donnée d'un arbre.
   * ATTENTION: Opération dangereuse, il faut garantir que le noeud où on 
   * fait la transplantation n'a plus d'enfant, où que l'on sera capable de
   * trouver ces enfants afin de les libérer!!!
   * @param destination adresse où on accrochera le sous-arbre
   * @param depart adresse de la racine du sous-arbre à transplanter
   */
  void
  transplanter (Noeud *destination, Noeud *depart)
  {
    if (destination == racine) racine = depart;
    else if (leNoeudEstUnEnfantDeGauche (destination)) destination->reqParent ()->asgEnfantGauche (depart);
    else destination->reqParent ()->asgEnfantDroite (depart);
    if (depart) depart->asgParent (*(destination->reqParent ()));
  }

public:

  /**
   * Rotation vers la gauche
   * @param x Adresse du noeud qui fait la rotation, ce noeud deviendra le 
   * l'enfant de son enfant actuel de droite
   */
  void
  rotationGaucheNoeud (Noeud* x)
  {
    if (!x->reqDroite ()) throw std::logic_error ("Rotation vers la gauche interdite: pas d'enfant à droite.");

    Noeud* y = x->reqDroite ();
    y->asgParent (*(x->reqParent ()));
    racine = (y->reqParent () != nullptr) ? racine : y;
    x->asgParent (*y);
    x->asgEnfantDroite (y->reqGauche ());
    y->reqGauche ()->asgParent (*x);
    y->asgEnfantGauche (x);
  }

  /**
   * Rotation vers la gauche
   * @param iter itérateur pointant au noeud qui fait la rotation.  Celui-ci 
   * deviendra lenfant de son actuel enfant de droite.
   */

  void
  rotationGauche (base_const_iterator iter)
  {
    rotationGaucheNoeud (iter.reqCourant ());
  }

  /**
   * Rotation vers la droite
   * @param y adresse du noeud qui va faire la rotation. Celui-ci deviendra 
   * l'enfant de son enfant actuel de gauche
   */

  void
  rotationDroiteNoeud (Noeud* y)
  {
    if (!y->reqGauche ()) throw std::logic_error ("Rotation vers la droite interdite: pas d'enfant à gauche.");

    Noeud* x = y->reqGauche ();
    x->asgParent (*(y->reqParent ()));
    racine = (x->reqParent () != nullptr) ? racine : x;
    y->asgParent (*x);
    y->asgEnfantGauche (x->reqDroite ());
    x->reqDroite ()->asgParent (*y);
    x->asgEnfantDroite (y);
  }

  /**
   * Rotation vers la droite
   * @param iter itérateur pointant au noeud qui va faire la rotation
   */

  void
  rotationDroite (base_const_iterator iter)
  {
    rotationDroiteNoeud (iter.reqCourant ());
  }

  /**
   * Rotation vers la gauche autour de la racine de l'arbre.  La nouvelle 
   * racine sera l'enfant gauche de la racine actuelle
   */

  void
  rotationGaucheAutourDuSommet ()
  {
    rotationGaucheNoeud (racine);
  }

  /**
   * Rotation droite vers la droite autour de la racine de l'arbre.  La 
   * nouvelle racine sera l'enfant droite de la racine actuelle
   */

  void
  rotationDroiteAutourDuSommet ()
  {
    rotationDroiteNoeud (racine);
  }


private:

  /** adresse de la racine de l'arbre */

  Noeud *racine;
};


#endif /* ARBREBINAIRE_H */

