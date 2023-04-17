#include <stdio.h>

int main() {
int wall_length, number_of_tribes, width, height, time, position, speed, attack_interval, number_of_attacks, i, j, k, wall_thickness[100000];

scanf("%d", &wall_length);
wall_length += 1;
for (i = 0; i<wall_length; i++){
  wall_thickness[i]=1;
}

scanf("%d", &number_of_tribes);

for (i=0; i<number_of_tribes; i++){
  scanf("%d %d %d %d %d %d %d", &width, &height, &time, &position, &speed, &attack_interval, &number_of_attacks);
  for (j=0; j<number_of_attacks; j++){
    for (k=position; k< position+width; k++){
      if (k < wall_length && k >= 0){
        if (height > wall_thickness[k] ){
          wall_thickness[k] = height;
        }
      }
      else if (k >= wall_length || k < 0){
        continue;
      }
    }
    position += speed*attack_interval;
  }
}

for (i=0; i<wall_length; i++){
    if (i == wall_length-1){
        printf("%d", wall_thickness[i]);
    }
    else{
        printf("%d ", wall_thickness[i]);
    }
}
printf("\n");
  return 0;
}

// #include <stdio.h>
//
// int main() {
// int wall_length, number_of_tribes, width, height, time, position, speed, attack_interval, number_of_attacks, i, j, k, wall_thickness[100000];
//
// scanf("%d", &wall_length);
// wall_length += 1;
// for (i = 0; i<wall_length; i++){
//   wall_thickness[i]=1;
// }
//
// scanf("%d", &number_of_tribes);
//
// for (i=0; i<number_of_tribes; i++){
//   scanf("%d %d %d %d %d %d %d", &width, &height, &time, &position, &speed, &attack_interval, &number_of_attacks);
//   for (j=0; j<number_of_attacks; j++){
//     for (k=position; k< position+width; k++){
//       if (height > wall_thickness[k] ){
//         wall_thickness[k] = height;
//       }
//     }
//     position += speed*attack_interval;
//   }
// }
//
// for (i=0; i<wall_length; i++){
//     if (i == wall_length-1){
//         printf("%d", wall_thickness[i]);
//     }
//     else{
//         printf("%d ", wall_thickness[i]);
//     }
// }
// printf("\n");
//   return 0;
// }
