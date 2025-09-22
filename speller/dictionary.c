// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table  待办事项：选择哈希表中的桶数
const unsigned int N = 26;
// Hash table  哈希表
node *table[N];

// Returns true if word is in dictionary, else false  如果词在词典中,返回true,否则返回false
bool check(const char *word)
{
    // TODO  代办事项
        // 计算单词的哈希值（注意：hash函数需要能处理大小写，或这里先转换为小写）
    int index = hash(word);
    // 从对应链表的头节点开始遍历
    node *current = table[index];
    if (current == NULL)
    {
        return false;
    }
    // 遍历整个链表
    while (current != NULL)
    {
        // 比较单词（不区分大小写）
        if (strcasecmp(word, current->word) == 0)
        {
            return true; // 找到匹配的单词
        }
        current = current->next; // 移动到下一个节点
    }

    // 遍历完链表仍未找到
    return false;
}

// Hashes word to a number  将单词散列为一个数字
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function  待办事项:将哈希函数转为大写
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false  将字典加载到内存中，如果成功则返回 true，否则返回 false
bool load(const char *dictionary)
{
    // TODO  代办事项
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    char buffer[45 + 1];
    bool current = true;
    if (file != NULL)
    {
        while (fscanf(file, "%45s", buffer) != EOF)
        {
            node *n = malloc(sizeof(node));
            if (n == NULL)
            {
                fclose(file);
                return false;
            }
            strcpy(n->word, buffer);
            int i = hash(buffer);
            n->next = table[i];
            table[i] = n;
        }

    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded  如果已加载，则返回字典中的字数；如果尚未加载，则返回 0
unsigned int size(void)
{
    // TODO  代办事项
    unsigned int count = 0;

    // 遍历哈希表的每个索引
    for (int i = 0; i < 26; i++)
    {
        // 遍历当前索引下的链表
        node *current = table[i];
        while (current != NULL)
        {
            count++;               // 计数当前节点
            current = current->next; // 移动到下一个节点
        }
    }

    return count;
}

// Unloads dictionary from memory, returning true if successful, else false  从内存中卸载字典，如果成功则返回 true，否则返回 false
bool unload(void)
{
    // TODO
        // 遍历每个字母对应的链表
    for (int i = 0; i < 26; i++)
    {
        node *current = table[i]; // 从链表头部开始

        // 遍历当前链表并释放每个节点
        while (current != NULL)
        {
            node *tmp = current;   // 保存当前节点
            current = current->next; // 移动到下一个节点
            free(tmp);             // 释放当前节点
        }
    }
    return true; // 所有链表都已释放
}
