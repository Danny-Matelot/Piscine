#include "menu.h"

Menu::Menu()
{

    /// Le cadre d'ensemble de l'interface; x y coin sup. gauche, largeur, hauteur
    /// Le fond sera gris clair et on pourra le bouger à la souris (drag & drop)


    m_top_box.set_frame(0, 0, LECRAN , HECRAN);
    m_top_box.set_bg_color(BLEU);
    m_top_box.set_moveable(false);

    /// Remplissage

    m_top_box.add_child( m_main_menu );

        m_main_menu.set_frame(0, 0, LECRAN, HECRAN);
        m_main_menu.set_bg_color(BLANC);
        m_main_menu.set_moveable(false);

        m_main_menu.add_child( m_nom_menu );
        m_nom_menu.set_message("MENU PRINCIPAL");
        m_nom_menu.set_gravity_y(grman::GravityY::Up);
        m_nom_menu.draw_border();
        m_nom_menu.set_margin(17);
        //m_nom_menu.set_dim(0,0);
        //m_nom_menu.set_padding();


            /// Bouton LOAD
        m_main_menu.add_child( m_but_load );
        m_but_load.set_frame(0,-20,320,16);
        m_but_load.set_bg_color(ROUGE);
        m_but_load.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);
        m_but_load.set_frame(LECRAN/2-320/2,HECRAN/2 - 16,320,16);
        m_but_load.add_child(m_txt_load);
        m_txt_load.set_message("LOAD");

            /// Bouton EDIT
        m_main_menu.add_child( m_but_edit );
        m_but_edit.set_bg_color(BLEU);
        m_but_edit.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);
        m_but_edit.set_frame(LECRAN/2-320/2,HECRAN/2  ,320,16);
        m_but_edit.add_child(m_txt_edit);
        m_txt_edit.set_message("EDIT");

            /// Bouton SAVE
        m_main_menu.add_child( m_but_save );
        m_but_save.set_bg_color(ROUGE);
        m_but_save.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);
        m_but_save.set_frame(LECRAN/2-320/2,HECRAN/2 + 16,320,16);
        m_but_save.add_child(m_txt_save);
        m_txt_save.set_message("SAVE");


}

Menu::~Menu()
{
    //dtor
}

void Menu::update()
{


    /// Si tous les widgets dépendants de l'objet sont dans une top box
    /// alors ce seul appel suffit (la propagation d'updates se fait ensuite automatiquement)
    m_top_box.update();

    /// Utilisation d'un bouton pour déclencher un événement
    /// L'accès à clicked() fait un reset : tant que le bouton n'est pas
    /// à nouveau cliqué les futurs accès à clicked seront faux
    /// ( Donc il faut appeler clicked() UNE FOIS ET UNE SEULE par update )

    if ( m_but_edit.clicked() )
    {
        std::cout << "EDIT !" << std::endl;
    }

    /// Utilisation de l'autre bouton (méchant clown) pour enlever un clown
    if ( m_but_load.clicked() )
    {
        std::cout << "LOAD !" << std::endl;
    }

    if ( m_but_save.clicked() )
    {
        std::cout << "SAVE !" << std::endl;
    }

}
