#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "members.h"

MemberNode* CreateMemberNode(Member member) {
    MemberNode* newnode = (MemberNode*)malloc(sizeof(MemberNode));
    newnode->data = member;
    newnode->next = NULL;
    return newnode;
}
void addMember(const char* filename, Member member) {
    FILE* file = fopen(filename, "a"); // Mở tệp trong chế độ ghi tiếp

    if (file == NULL) {
        printf("Không thể mở tệp %s\n", filename);
        return;
    }

    // Ghi thông tin thành viên vào tệp
    fprintf(file, "%s,%s,%s,%s\n", member.uid, member.roomNumber, member.name, member.licensePlate);

    fclose(file); // Đóng tệp sau khi ghi xong
}
// Hàm xóa thông tin thành viên dựa vào UID
void deleteMember(const char* filename, const char* uid) {
    FILE* file = fopen(filename, "r");
    FILE* tempFile = fopen("temp.csv", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Không thể mở tệp %s\n", filename);
        return;
    }

    char buffer[1024];
    int found = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        char token[20];
        sscanf_s(buffer, "%[^,],", token, sizeof(token));

        if (strcmp(uid, token) != 0) {
            // Sao chép các dòng khác như cũ
            fputs(buffer, tempFile);
        }
        else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    if (!found) {
        printf("Không tìm thấy thành viên với UID: %s\n", uid);
        remove("temp.csv");
    }
    else {
        remove(filename);
        rename("temp.csv", filename);
        printf("Đã xóa thông tin thành viên với UID: %s\n", uid);
    }
}
void editMember(const char* filename, Member updatedMember) {
    // Mở tệp để đọc danh sách thành viên
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Không thể mở tệp %s\n", filename);
        return;
    }

    // Tạo danh sách thành viên
    Member members[100];
    int numMembers = 0;
    while (fscanf_s(file, "%[^,],%[^,],%[^,],%[^\n]\n",
        members[numMembers].uid,
        sizeof(members[numMembers].uid),
        members[numMembers].roomNumber,
        sizeof(members[numMembers].roomNumber),
        members[numMembers].name,
        sizeof(members[numMembers].name),
        members[numMembers].licensePlate,
        sizeof(members[numMembers].licensePlate)) != EOF) {
        numMembers++;
    }

    // Tìm thành viên cần chỉnh sửa và cập nhật thông tin
    for (int i = 0; i < numMembers; i++) {
        if (strcmp(members[i].uid, updatedMember.uid) == 0) {
            strcpy_s(members[i].name, sizeof(members[i].name), updatedMember.name);
            strcpy_s(members[i].roomNumber, sizeof(members[i].roomNumber), updatedMember.roomNumber);
            strcpy_s(members[i].licensePlate, sizeof(members[i].licensePlate), updatedMember.licensePlate);
            break;
        }
        else if (strcmp(members[i].licensePlate, updatedMember.licensePlate) == 0) {
            strcpy_s(members[i].name, sizeof(members[i].name), updatedMember.name);
            strcpy_s(members[i].roomNumber, sizeof(members[i].roomNumber), updatedMember.roomNumber);
            strcpy_s(members[i].uid, sizeof(members[i].uid), updatedMember.uid);
            break;
        }
    }
    // Đóng tệp
    fclose(file);

    // Mở tệp để ghi danh sách thành viên đã cập nhật
    if (fopen_s(&file, filename, "w") != 0) {
        printf("Không thể mở tệp %s\n", filename);
        return;
    }

    // Ghi danh sách thành viên vào tệp
    for (int i = 0; i < numMembers; i++) {
        fprintf(file, "%s,%s,%s,%s\n", members[i].uid, members[i].roomNumber, members[i].name, members[i].licensePlate);
    }

    // Đóng tệp
    fclose(file);
}
int searchByUID(const Member* members, int numMembers, const char* uid) {
    for (int i = 0; i < numMembers; i++) {
        if (strcmp(members[i].uid, uid) == 0) {
            printf("Information of member with UID %s: Roomnumber: %s, Name: %s, LicensePlate:%s\n", members[i].uid, members[i].roomNumber, members[i].name, members[i].licensePlate);
            return i; // Trả về chỉ số của thành viên có UID tương ứng
        }
    }
    return -1; // Không tìm thấy
}
int searchByLicensePlate(const Member* members, int numMembers, const char* licensePlate) {
    for (int i = 0; i < numMembers; i++) {
        if (strcmp(members[i].licensePlate, licensePlate) == 0) {
            printf("Information of member with LicensePlate %s: UID:%s, Roomnumber: %s, Name: %s \n", members[i].licensePlate, members[i].uid, members[i].roomNumber, members[i].name);
            return i; // Trả về chỉ số của thành viên có UID tương ứng
        }
    }
    return -1; // Không tìm thấy
}

Member searchMember(const char* filename, const char* searchValue, SearchFunction searchFunc) {

    // Đọc danh sách thành viên từ tệp (giả sử đã có sẵn)
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Không thể mở tệp.\n");
        return;
    }
    Member members[100];
    int numMembers = 0;

    int foundIndex = searchFunc(members, numMembers, searchValue);
    if (foundIndex != 1) {
        return members[foundIndex];
    }
    else {
        Member notFoundMember = { "", "", "Cant find", "" };
        return notFoundMember;

    }
}

