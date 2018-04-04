#ifndef MENU_H
#define MENU_H


#include "grman/grman.h"
#include <iostream>
#include <stack>

/// BASE SUR LE CODE DE M. FERCOQ DANS L'EXEMPLE DES CLOWNS

class Menu
{
    public:
        /** Default constructor */
        Menu();
        /** Default destructor */
        virtual ~Menu();

        void lancer();

    protected:

        /// Utiliser une top_box de type WidgetBox pour encapsuler
        /// tous les �l�ments de l'interface associ�s � votre objet
        grman::WidgetBox m_top_box;

        /// Les Widgets qui constitueront l'interface de l'objet
        grman::WidgetBox m_main_menu;
        grman::WidgetText m_txt_load;      //
        grman::WidgetButton m_but_load;
        grman::WidgetText m_txt_save;      // Sera le clown marcheur au milieu
        grman::WidgetButton m_txt_save;
        grman::WidgetText m_txt_edit;
        grman::WidgetButton m_but_edit;       // Sera la boite � cocher en bas � gauche (faire marcher le clown)



        std::stack<grman::WidgetImage *> m_options;     // Exp�rimental : permettra de gerer le nombre d'option dans le menu
                                                        // pas encore s�r � quoi �a sert, mais sur un malentendu, �a peut servir

    private:
};

#endif // MENU_H
