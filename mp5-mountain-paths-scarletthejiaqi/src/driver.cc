#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "color.hpp"
#include "path.hpp"
#include "path_image.hpp"
#include <iostream>
#include <vector>
#include <string>

// int main() {
//     ElevationDataset set = ElevationDataset(5,"/home/vagrant/src/mp5-mountain-paths-scarletthejiaqi/example-data/ex_input_data/prompt_5w_2h.dat",2);
//     // std::cout<<set.MaxEle()<<std::endl;
//     // std::cout<<set.MinEle()<<std::endl;
//     // for (unsigned int row = 0; row < 2; ++row) {
//     //     for (unsigned int col = 0; col < 5; ++col) {
//     //         std::cout<<set.DatumAt(row,col)<<std::endl;
//     //     }
//     // }
//     GrayscaleImage image = GrayscaleImage("/home/vagrant/src/mp5-mountain-paths-scarletthejiaqi/example-data/ex_input_data/prompt_5w_2h.dat",5,2);
//     image.ToPpm("ppmgrey");
//         // for (unsigned int row = 0; row < 2; ++row) {
//         //     for (unsigned int col = 0; col < 5; ++col) {
//         //         std::cout<<image.ColorAt(row,col).Blue()<<std::endl;
//         //     }
//         // }
//     PathImage pathimage = PathImage(image,set);
//     // for (unsigned int i = 0; i < pathimage.Paths().size(); ++i) {
//     //     std::cout<<pathimage.Paths().at(i).EleChange()<<std::endl;
//     // }
//     pathimage.ToPpm("ppmpath");
// }

