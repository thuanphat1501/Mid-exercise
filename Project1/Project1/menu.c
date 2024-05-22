#define _CRT_SECURE_NO_WARNINGS
/*
* File: Menu.c
* Author: Hong Thuan Phat
* Date: 20/5/2024
* Description: This file contains all the functions/methods for Menu
*/
#include"menu.h"
#include"stdio.h"
#include"stdint.h"

void Menu() {
	printf("\n\n\t***Apartment Building Residents Information Management System***\n\n");
	printf("\t\t\tMAIN MENU\n");
	printf("\t\t=======================\n");
	printf("\t\t[1] Add A New Resident.\n");
	printf("\t\t[2] Delete The Information of The Resident.\n");
	printf("\t\t[3] Update The Information of The Resident.\n");
	printf("\t\t[4] Search for A Resident according to UID/License Plate.\n");
	printf("\t\t[5] Exit the Program.\n");
	printf("\t\t=======================\n");
	printf("\t\tEnter The Choice: ");
}
void runProgram() {
	Menu();
	Member member;
	char key[20];
	char option;
	printf("Nhap lua chon cua ban (1-5): ");
	scanf("%d", &option);
	switch (option) {
	case 1: {
		printf("Enter UID: ");
		scanf("%s", member.uid);
		printf("Enter Room Number: ");
		scanf("%s", member.roomNumber);
		printf("Enter Name: ");
		scanf("%s", member.name);
		printf("Enter License Plate: ");
		scanf("%s", member.licensePlate);
		addMember(FILE_CSV,member);
		break;
	}
	case 2: {
		printf("Enter the UID of the resident to detele: ");
		scanf("%s", key);
		deleteMember(FILE_CSV, key);
		break;
	}
	case 3: {
		Member new_member;
		printf("enter the uid for update the information of the resident:");
		scanf("%s", key);

		printf("enter the new name: \n");
		scanf("%s", new_member.name);
		printf("enter the new room number: \n");
		scanf("%s", new_member.roomNumber);
		printf("enter the new license plate: \n");
		scanf("%s", new_member.licensePlate);
		editMember(FILE_CSV, new_member);
	}
	case 4: {
		printf("Enter the UID of the resident to find: ");
		//scanf("%s", key);
		//searchMember(FILE_CSV, key,);
		break;
	}
	case 5: {
		printf("Exiting program.\n");
		break;
	}
	default:
		printf("Invalid option.\n");
	}
}