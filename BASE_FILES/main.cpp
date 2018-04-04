#include "grman/grman.h"
#include <iostream>


int main()
{
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du r�pertoire o� se trouvent les images � charger
    grman::set_pictures_path("pics");

    /// Un exemple d'assemblage de widgets
    Menu m;

    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement � des frameworks plus avanc�s )
    while ( !key[KEY_ESC] )
    {
        /// Il faut appeler les m�thodes d'update des objets qui comportent des widgets


        /// Mise � jour g�n�rale (clavier/souris/buffer etc...)

    }

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();
