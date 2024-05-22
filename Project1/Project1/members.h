#pragma once
#define _CRT_SECURE_NO_WARNINGS
/*
* File: member.h
* Author: Hong Thuan Phat
* Date: 20/5/2024
* Description: This file contains all the functions prototypes for Membership management library.
*/
#ifndef __MEMBER_H
#define __MEMBER_H
#define FILE_CSV "thanh_vien.csv"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Member {
	char uid[20];
	char roomNumber[10];
	char name[50];
	char licensePlate[20];
} Member;

typedef struct MemberNode {
	Member data;
	struct MemberNode* next;
} MemberNode;
typedef int (*SearchFunction)(const Member*, int, const char*);


void addMember(const char* filename, Member member);
void deleteMember(const char* filename, const char* uid);
void editMember(const char* filename, Member updatedMember);
Member searchMember(const char* filename, const char* searchValue, SearchFunction searchFunc);



#endif // !__MEMBER_H
