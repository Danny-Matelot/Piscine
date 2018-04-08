#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <stack>
#include "grman/grman.h"
#include "libprojet.h"
#include "graph.h"

/// BASE SUR LE CODE DE M. FERCOQ DANS L'EXEMPLE DES CLOWNS

class Menu
{
    public:
        /** Default constructor */
        Menu();
        /** Default destructor */
        virtual ~Menu();

        void update(Graph& g, bool& principal);

    protected:

        /// Utiliser une top_box de type WidgetBox pour encapsuler
        /// tous les éléments de l'interface associés à votre objet
        grman::WidgetBox m_top_box;

            /// Les Widgets qui constitueront l'interface de l'objet
            grman::WidgetBox m_main_menu;       //Contiendra tout les options du premier menu à apparaitre

                    /// Infos sur le graphe actuel:
                grman::WidgetText m_graphe_actuel; // Afficher en haut à droite pour indique qel graphe est chargé
                grman::WidgetText m_nom_menu; // Afficher en haut milieu pour dire que c'dst le main menu
                grman::WidgetText m_loaded_file;

                    ///Options du Menu
                grman::WidgetText m_txt_load;       // Texte pour charger un graphe
                grman::WidgetButton m_but_load;     // Bouton: cliquer pour aller au sous menu chargement

                grman::WidgetText m_txt_save;       // Texte pour sauvegarder le graphe actuel
                grman::WidgetButton m_but_save;     // Bouton: sous menu de sauvegarde du graphe

                grman::WidgetText m_txt_edit;       // Texte pour visualiser et éditer un graphe
                grman::WidgetButton m_but_edit;     // Buton: menu cf ligne du dessus



        std::stack<grman::WidgetImage *> m_options;     // Expérimental : permettra de gerer le nombre d'option dans le menu
                                                        // pas encore sûr à quoi ça sert, mais sur un malentendu, ça peut servir

    private:
};
#endif // MENU_H
