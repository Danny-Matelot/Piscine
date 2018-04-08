#include "graph.h"

/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les éléments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de réglage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0 , 100.0); // Valeurs arbitraires, à adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( std::to_string(idx) );
}


/// Gestion du Vertex avant l'appel à l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_value vers le slider associé
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donnée m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Vertex après l'appel à l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_value locale
    m_value = m_interface->m_slider_value.get_value();
}



/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les éléments de l'interface
EdgeInterface::EdgeInterface(Vertex& from, Vertex& to)
{
    // Le WidgetEdge de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating EdgeInterface between vertices having no interface" << std::endl;
        throw "Bad EdgeInterface instanciation";
    }
    m_top_edge.attach_from(from.m_interface->m_top_box);
    m_top_edge.attach_to(to.m_interface->m_top_box);
    m_top_edge.reset_arrow_with_bullet();

    // Une boite pour englober les widgets de réglage associés
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de réglage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0 , 100.0); // Valeurs arbitraires, à adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

    //from.m_out.push_back(&to);
    //to.m_in.push_back(&from);

}


/// Gestion du Edge avant l'appel à l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_weight vers le slider associé
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donnée m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Edge après l'appel à l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}



/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(80,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);
}


/// Méthode spéciale qui construit un graphe arbitraire (démo)
/// Cette méthode est à enlever et remplacer par un système
/// de chargement de fichiers par exemple.
/// Bien sûr on ne veut pas que vos graphes soient construits
/// "à la main" dans le code comme ça.
void Graph::make_example()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    /// Les sommets doivent être définis avant les arcs
    // Ajouter le sommet d'indice 0 de valeur 30 en x=200 et y=100 avec l'image clown1.jpg etc...
    add_interfaced_vertex(0, 30.0, 200, 100, "clown1.jpg");
    add_interfaced_vertex(1, 60.0, 400, 100, "clown2.jpg");
    add_interfaced_vertex(2,  50.0, 200, 300, "clown3.jpg");
    add_interfaced_vertex(3,  0.0, 400, 300, "clown4.jpg");
    add_interfaced_vertex(4,  100.0, 600, 300, "clown5.jpg");
    add_interfaced_vertex(5,  0.0, 100, 500, "bad_clowns_xx3xx.jpg", 0);
    add_interfaced_vertex(6,  0.0, 300, 500, "bad_clowns_xx3xx.jpg", 1);
    add_interfaced_vertex(7,  0.0, 500, 500, "bad_clowns_xx3xx.jpg", 2);

    /// Les arcs doivent être définis entre des sommets qui existent !
    // AJouter l'arc d'indice 0, allant du sommet 1 au sommet 2 de poids 50 etc...
    add_interfaced_edge(0, 1, 2, 50.0);
    add_interfaced_edge(1, 0, 1, 50.0);
    add_interfaced_edge(2, 1, 3, 75.0);
    add_interfaced_edge(3, 4, 1, 25.0);
    add_interfaced_edge(4, 6, 3, 25.0);
    add_interfaced_edge(5, 7, 3, 25.0);
    add_interfaced_edge(6, 3, 4, 0.0);
    add_interfaced_edge(7, 2, 0, 100.0);
    add_interfaced_edge(8, 5, 2, 20.0);
    add_interfaced_edge(9, 3, 7, 80.0);
}

/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update()
{
    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();
    ///pour tester les voisins
       /* for(auto &elt : m_vertices)
        {
        std::cout<<elt.first<<"a comme voisins:"<<std::endl;
            for(auto &it : elt.second.m_out )
            {
                std::cout<<it<<std::endl;
            }
        }*/


}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Création d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Vertex(value, vi);
}

/// Aide à l'ajout d'arcs interfacés
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight)
{
    if ( m_edges.find(idx)!=m_edges.end() )
    {
        std::cerr << "Error adding edge at idx=" << idx << " already used..." << std::endl;
        throw "Error adding edge";
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding edge";
    }

    EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);

    m_interface->m_main_box.add_child(ei->m_top_edge);
    m_edges[idx] = Edge(weight, ei);
    m_edges[idx].m_from=id_vert1;
    m_edges[idx].m_to=id_vert2;
    m_vertices[id_vert1].m_out.push_back(id_vert2);
    m_vertices[id_vert2].m_in.push_back(id_vert1);

}


void Graph:: DFS(std::stack <int> &DFS_S, std::stack <int> &V_o_p, int &S_d_d)
{
    int interm_var(-1);//pour recuperer le numero de sommet qu'on va ajouter (ou pas) dans les piles
    bool neighboor_check(true);//variable pour verifier si on a les voisins non-visitees

    while(S_d_d<0)//tant que on n'as pas de sommet e depart pour notre dfs
    {
       for(auto &it: m_vertices)//le premier sommet non marque qu'on trouve devient notre sommet de depart
       {
           if(it.second.marker==false)
           {
              S_d_d=it.first;
           }
       }
       DFS_S.push(S_d_d);
       m_vertices[DFS_S.top()].marker=true;
    }
    neighboor_check=false;
    for(auto &it :m_vertices[DFS_S.top()].m_out)//on cherche les voisins non marquees
    {

        if(m_vertices[it].marker==false)//si on en trouve on le prends pour ajouter dans la pile (du coup ca sera le dernier voisin non marque de la liste qui sera ajoute)
        {
           interm_var=it;
           neighboor_check=true;

        }
    }

    if(neighboor_check)//si on a trouve un voisin non marque on l'ajoute dans la pile de DFS et on le marque
    {
       DFS_S.push(interm_var);
       m_vertices[interm_var].marker=true;
    }
    else//si il n'y a pas de voisins non marquees
    {
       if(DFS_S.size()>1)//si pile contient + qu'un element
       {
          V_o_p.push(DFS_S.top());//on ajoute le sommet avec le temps de passage + eleve dans notre pile de kosaraju
          DFS_S.pop();//on supprime cette sommet de pile de DFS pour verifier les voisins de sommet precedent
       }
       else //pour eviter les problemes de memoire, quand dans la pile DFS il ne reste + qu'un sommet, on fait la meme chose qu'avant, et apres ca on indique qu'il faudra parcourir le graph pour trouver un nouvelle sommet de depart(si besoin)
       {
          V_o_p.push(DFS_S.top());
          DFS_S.pop();
          S_d_d=-1;
       }
    }
}
void Graph:: Inversed_DFS(std::stack <int> &DFS_S, std::stack <int> & V_o_p, int &color, int &S_d_d)
{
    int interm_var(-1);
    bool neighboor_check(true);
    ///si on n'as pas encore choisi le sommet de depart, on le choisit
    while(S_d_d==-1)
    {  ///LE principe de Kosaraju est suivant: on prends la sommet de top de pile (le sommet avec le temps de passage + eleve), et on y applique le DFS
       if(m_vertices[V_o_p.top()].marker==false)//des que dans notre
       {
         S_d_d=V_o_p.top();
         DFS_S.push(S_d_d);
         m_vertices[DFS_S.top()].marker=true;
         color++;
         m_vertices[DFS_S.top()].m_color=color;
       }
       else
       {
         V_o_p.pop();
       }
    }
    //vu qu'on doit faire le DFS pour le transposee de graphique, au lieu d'inverser toutes les
    neighboor_check=false;
    for(auto &it :m_vertices[DFS_S.top()].m_in)//si on a trouve le voisin non marque, on le prends pour ensuite ajouter au top de pile
    {
        if(m_vertices[it].marker==false)
        {
           interm_var=it;
           neighboor_check=true;
        }
    }

    if(neighboor_check)//on l'ajoute au top de pile et on le marque+ on lui affectue a un composant fortement connexe qu'on parcours en ce moment
    {
       DFS_S.push(interm_var);
       m_vertices[interm_var].marker=true;
       m_vertices[interm_var].m_color=color;
    }
    else//si il n'y a pas de voisins
    {
       if(DFS_S.size()>1)
       {
          DFS_S.pop();
       }
       else
       {  DFS_S.pop();
          S_d_d=-1;
       }
    }
}
void Graph:: Search_of_CFC_Kosaraju()
{
    int i;
    int color(0);//variable qui indiquera l'appartenance d'un sommet a un composant fortement connexe concrete
    int Sommet_de_depart=-1;//sommet de depart pour les DFS (-1 car on ne peut pas tomber sur un sommet ave cun numero negatif)
    std::stack<int> DFS_stack;//pile pour faire le DFS
    std::stack <int> Verticles_in_order_of_passage;//pile qui contiendra les sommets dans l'ordre de passage specifique(des qu'on a plus de voisins a visiter, sommet est ajoute dans cette pile)
    bool check;//variable pour verifier si on a marque toutes les sommets


    check=false;
    do
    {

       check=true;

       for(auto &it : m_vertices)//si on trouvera un sommet non marque boucle continue a tourner
       {
           if(it.second.marker==false)
           check=false;
       }
       if(!check)//si il y a les sommets non marquees on effectue notre DFS modifie
       this->DFS(DFS_stack, Verticles_in_order_of_passage, Sommet_de_depart);


    }while(check!=true);//tant qu'on n'a pas marque toutes les sommets



    ///on reset le marquage pour appliquer le DFS encore une fois en suivant l'algo de Kosaraju
    for(auto &it : m_vertices)
       {
          it.second.marker=false;
       }


    ///La meme chose qu'avant, mais ce fois ci on appliquera autre DFS pour le aretes inversees (transposee de graph), chaque itteration complet de DFS nous donnera un composant fortement connexe
    check=false;
    Sommet_de_depart=-1;
    do
    {
       check=true;

       for(auto &it : m_vertices)
       {
          if(it.second.marker==false)
             check=false;
       }
       if(!check)
       this->Inversed_DFS(DFS_stack, Verticles_in_order_of_passage, color, Sommet_de_depart);

    }while(check!=true);

    ///algorithme est termine, on resete le marquage des sommets a 0
    for(auto &it : m_vertices)
    {
        it.second.marker=false;
        std::cout<<it.first<<" "<<it.second.m_color<<std::endl;
    }

}
