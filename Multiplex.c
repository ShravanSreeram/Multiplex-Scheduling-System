// Multiplex_Cinema_hall.C
// This program aims to organize data for a multiplex cinema hall by determining
// the appropriate number of screens for each movie to maximize the profit

#include <stdio.h>
void user_login();          // Creating User Login credential
void Input_movie_details(); // Recieving Movie name and demand score as input
                            // and initialising priority score and number of
                            // screens as 0
int Priority_calculation(
    int arr[10][2][3],
    int len); // Using the demand score to calculate priority order
int calculate_screen_count(
    int arr[][2][3],
    int len); // Using the priority score to calculate number of screens
void Weekend_success_rate(
    int arr[][2][3], int n,
    char names[][30]); // Input success rate for the existing movies
void Weekend_priority_updation(
    int arr[][2][3],
    int n); // Updating priority order based on success rate of movies
void Display_output(int arr[][2][3], char name[10][30],
                    int len); // To display the output in the required format
void Write_in_file(int arr[][2][3], char name[10][30],
                   int len);  // To write the data into a csv file
void Read_from_file(int len); // To retrieve data from the file

int arr[10][2][3], oldlen, flag = 0; // oldlen is used to count the number of
                                     // movies from the previous weeks
char name[10][30];


void user_login() {
  int user_login, x = 10, n;
  printf("Enter the password in digits");
  printf("\n Create a password:");
  scanf("%d", &user_login);

  while (user_login != n) {
    printf("\n Enter the password:");
    scanf("%d", &n);

    if (user_login == n) {
      printf("Correct password \n");
      Input_movie_details();

    } else {
      printf("Wrong password, try another");
    }
    printf("\n");
  }
}

void main() {
  int arr[10][2][3];
  user_login();
}

void Input_movie_details() {
  int i = 0, n;
  printf("Enter the number of movies releasing this week:");
  scanf("%d", &n);
  if (flag > 0) {
    i = i + oldlen;
    n = n + oldlen;
  }
  for (i; i < n; i++) {
    printf("Enter the name of movie:");
    scanf("%s", name[i]);
    printf("Enter the demand score of the movie:");
    arr[i][1][0] = 0;
    arr[i][1][2] = 0;
    scanf("%d", &arr[i][1][1]);
  }
  for (i = 0; i < n; i++) {
    printf("Name of the movie: %s \n", name[i]);
    printf("Priority order %d Demand score %d No of screens %d \n",
           arr[i][1][0], arr[i][1][1], arr[i][1][2]);
  }
  Priority_calculation(arr, n);
}

int Priority_calculation(int arr[10][2][3], int len) {
  printf("Entered funct priorty calculation \n");
  int i;
  for (i = 0; i < len; i++) {
    if (arr[i][1][0] == 0 && arr[i][1][1] <= 10) {
      arr[i][1][0] = arr[i][1][1] / 2;
    }
  }
  calculate_screen_count(arr, len);
  return 0;
}






int calculate_screen_count(int arr[][2][3], int len) {
  printf("Entered funct screens\n");
  int i, sum = 0, sc = 0, p = 5;
  for (i = 0; i < len; i++) {
    sum = sum + arr[i][1][0];
  }

  for (i = 0; i < len; i++) {
    arr[i][1][2] = arr[i][1][0] * 16 / sum;
    sc = sc + arr[i][1][2];
  }
  while (sc < 16) {
    for (i = len - 1; i >= 0; i--) {
      if (arr[i][1][0] == p && sc < 16) {
        arr[i][1][2]++;
        sc = sc + 1;
      }
    }
    p--;
  }
  for (i = 0; i < len; i++) {
    if (arr[i][1][1] < 11)
      printf("Priority order %d Demand score %d No of screens %d \n",
             arr[i][1][0], arr[i][1][1], arr[i][1][2]);
    else
      printf("Priority order %d Success rate %d No of screens %d \n",
             arr[i][1][0], arr[i][1][1], arr[i][1][2]);
  }
  Display_output(arr, name, len);
  Write_in_file(arr, name, len);
  Read_from_file(len);
  int flag = 0;
  if (arr[oldlen][1][1] <= 10)
    Weekend_success_rate(arr, len, name);
  else
    printf("Weekend details updated\n");

  return 0;
}

void Weekend_success_rate(int arr[][2][3], int n, char names[][30]) {
  for (int i = 0; i < n; i++) {
    if (arr[i][1][2] != 0) {
      printf("Enter the success rate in percent for the movie %s:", names[i]);
      scanf("%d", &arr[i][1][1]);
    } else {
      arr[i][1][0]= 0;
    }
  }
  Weekend_priority_updation(arr, n);
}
void Weekend_priority_updation(int arr[][2][3], int n) {
  int i;
  for (i = 0; i < n; i++) {
    if (arr[i][1][1] >= 80)
      arr[i][1][0] += 1;
    else if (arr[i][1][1] > 60)
      arr[i][1][0] += 0;
    else if (arr[i][1][1] > 50)
      arr[i][1][0] -= 1;
    else if (arr[i][1][1] > 30)
      arr[i][1][0] -= 2;
    else if (arr[i][1][1] <= 30) {
      arr[i][1][0] = 0;
      arr[i][1][1] = 11;
    }

    if (arr[i][1][0] > 5)
      arr[i][1][0] = 5;
    if (arr[i][1][0] < 0)
      arr[i][1][0] = 0;
  }
  calculate_screen_count(arr, n);
  flag = 1;
  oldlen = n;
  Input_movie_details();
  for (i = 0; i < n; i++) {
    printf("Name of the movie: %s \n", name[i]);
  }
}

void Display_output(int arr[][2][3], char name[10][30], int len) {
  int i, j, c = 0, x = 0;
  printf("WEEKDAYS:\n\n");
  for (i = 0; i < len; i++) {
    for (j = 0; j < arr[i][1][2]; j++) {
      if (c < 9)
        printf("Screen 0%d : %s      ", ++c, name[i]);
      else
        printf("Screen %d : %s      ", ++c, name[i]);
      if (c % 3 == 1)
        printf("10:00     1:30    6:00\n\n");
      else if (c % 3 == 2)
        printf("10:30     2:00    6:30\n\n");
      else
        printf("11:00     2:30    7:00\n\n");
    }
  }
  printf("WEEKENDS:\n\n");
  for (i = 0; i < len; i++) {
    for (j = 0; j < arr[i][1][2]; j++) {
      if (x < 9)
        printf("Screen 0%d : %s      ", ++x, name[i]);
      else
        printf("Screen %d : %s      ", ++x, name[i]);
      if (x % 3 == 1)
        printf("6:00    09:30    1:30    5:30    09:30\n\n");
      else if (x % 3 == 2)
        printf("6:30    10:00    2:00    6:00    10:00\n\n");
      else
        printf("7:00    10:30    2:30    6:30    10:30\n\n");
    }
  }
}

void Write_in_file(int arr[][2][3], char name[10][30], int len) {
  printf("Entered funct Write_in_file %d \n", len);
  FILE *f;
  int i;
  f = fopen("sample.csv", "w");
  fprintf(f, "Movie Number,Priority,No of screens,Name \n");
  for (i = 0; i < len; i++) {

    fprintf(f, "%d,%d,%d,%s \n", i + 1, arr[i][1][0], arr[i][1][2], name[i]);
  }
  fclose(f);
}
void Read_from_file(int len) {
  char c[60];

  FILE *f;
  char n[10];
  f = fopen("sample.csv", "r");
  int x, y, z;
  fgets(c, 60, f);
  printf("%s\n", c);
  for (int i = 0; i < len; i++) {
    fscanf(f, "%d,%d,%d,%s", &x, &y, &z, n);
    printf("%d,%d,%d,%s\n", x, y, z, n);
  }

  fclose(f);
}