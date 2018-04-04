#include "grman/grman.h"
#include <iostream>


int main()
{
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");

    /// Un exemple d'assemblage de widgets
    Menu m;

    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {
        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets


        /// Mise à jour générale (clavier/souris/buffer etc...)

    }

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();
