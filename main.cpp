#include <iostream>
#include <gtest/gtest.h>
const int size = 8;
class Set
{
private:
    int set[size];
public:
    Set()
    {
        for(int i = 0 ;i < size; i++)
        {
            set[i] = 0;
        }
    }

    ~Set() = default ;

    int get_index(unsigned char elem)
    {
        int result;
        result = elem / 32;
        return result;
    }
    int get_shift_count(unsigned char elem)
    {
        int result;
        result = elem % 32;
        return result;
    }
    void add(unsigned char elem)
    {
        int index;
        index = get_index(elem);
        int count;
        count = get_shift_count(elem);
        set[index] |= 1 << count;
    }
    void remove(unsigned char elem)
    {
        int index;
        index = get_index(elem);
        int count;
        count = get_shift_count(elem);
        set[index] = set[index] & ( ~ ( 1 << count) );
    }
    Set merge(Set set1)
    {
        Set result;
        for(int i = 0 ;i<size; i++)
        {
            result.set[i] = set[i] | set1.set[i];
        }
        return result;
    }
    Set intersection(Set set1)
    {
        Set result;
        for(int i = 0 ;i<size; i++)
        {
            result.set[i] = set[i] & set1.set[i];
        }
        return result;
    }
    Set difference(Set set2)
    {
        Set result;
        for(int i = 0; i < size;i++)
        {
            result.set[i] = set[i] & ( ~ ( set2.set[i] ) );
        }
        return result;
    }
    void complete_set()
    {
        for(int i = 0 ;i < size; i++)
        {
            set[i] = INT_MAX;
        }
    }
    Set absolute_complement()
    {
        Set result;
        result.complete_set();
        for(int i = 0 ;i < size; i++)
        {
            result.set[i] = result.set[i] & ( ~ ( set[i] ) );
        }
        return result;
    }
    bool find(char elem)
    {
        bool result;
        int index = get_index(elem);
        int count;
        count = get_shift_count(elem);
        int f = 0 ;
        f = 1<<count;
        result  = set[index] &  f;
        return result;
    }
};
TEST(Find,set1)
{
    Set set;
    set.add('a');
    set.add('f');
    set.add('*');
    set.add('g');
    set.add(2);
    set.add(1);
    set.add(4);
    EXPECT_EQ(true,set.find('a'));
    EXPECT_EQ(true,set.find('f'));
    EXPECT_EQ(true,set.find('*'));
    EXPECT_EQ(true,set.find('g'));
    EXPECT_EQ(true,set.find(1));
    EXPECT_EQ(true,set.find(2));
    EXPECT_EQ(true,set.find(4));
    EXPECT_EQ(false,set.find(5));
    EXPECT_EQ(false,set.find('q'));
}
TEST(Remove,set1)
{
    Set set;
    set.add('a');
    set.add('f');
    EXPECT_EQ(true,set.find('a'));
    EXPECT_EQ(true,set.find('f'));
    set.remove('a');
    set.remove('f');
    EXPECT_EQ(false ,set.find('a'));
    EXPECT_EQ(false ,set.find('f'));
}
TEST(Merge,set1)
{
    Set set;
    set.add('a');
    set.add('f');
    set.add('*');
    set.add('g');
    Set set1;
    set1.add(2);
    set1.add(1);
    set1.add(4);
    Set result = set.merge(set1);
    EXPECT_EQ(true,result.find('a'));
    EXPECT_EQ(true,result.find('f'));
    EXPECT_EQ(true,result.find('*'));
    EXPECT_EQ(true,result.find('g'));
    EXPECT_EQ(true,result.find(1));
    EXPECT_EQ(true,result.find(2));
    EXPECT_EQ(true,result.find(4));
}
TEST(Intersection,set1)
{
    Set set;
    set.add('a');
    set.add('f');
    set.add('*');
    set.add('g');
    Set set1;
    set1.add('a');
    set1.add('f');
    set1.add(4);
    set1.add(5);
    set1.add(6);
    Set result;
    result = set.intersection(set1);
    EXPECT_EQ(true,result.find('a'));
    EXPECT_EQ(true,result.find('f'));
    EXPECT_EQ(false,result.find('*'));
    EXPECT_EQ(false,result.find('g'));
    EXPECT_EQ(false,result.find(4));
    EXPECT_EQ(false,result.find(5));
    EXPECT_EQ(false,result.find(6));
}
TEST(Difference,set1)
{
    Set set;
    set.add('a');
    set.add('f');
    set.add('*');
    set.add('g');
    Set set1;
    set1.add('a');
    set1.add('f');
    set1.add(4);
    set1.add(5);
    set1.add(6);
    Set result = set.difference(set1);
    EXPECT_EQ(false,result.find('a'));
    EXPECT_EQ(false,result.find('f'));
    EXPECT_EQ(true,result.find('*'));
    EXPECT_EQ(true,result.find('g'));
    EXPECT_EQ(false,result.find(4));
    EXPECT_EQ(false,result.find(5));
    EXPECT_EQ(false,result.find(6));
}
TEST(Absolute_completment,set1)
{
    Set set;
    set.add(4);
    set.add(5);
    set.add(6);
    set.add(2);
    set.add(3);
    set.add('a');
    set.add(')');
    Set result;
    result = set.absolute_complement();
    EXPECT_EQ(false,result.find('a'));
    EXPECT_EQ(false,result.find(')'));
    EXPECT_EQ(false,result.find(2));
    EXPECT_EQ(false,result.find(3));
    EXPECT_EQ(false,result.find(4));
    EXPECT_EQ(false,result.find(5));
    EXPECT_EQ(false,result.find(6));
    EXPECT_EQ(true,result.find('h'));
    EXPECT_EQ(true,result.find(8));
    EXPECT_EQ(true,result.find(9));
    EXPECT_EQ(true,result.find('g'));
    EXPECT_EQ(true,result.find('y'));
    EXPECT_EQ(true,result.find('e'));
    EXPECT_EQ(true,result.find('w'));
}
int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
/*int main()
{
    Set set;
    Set set2;
    set.add(4);
    set.add(5);
    set.add(6);
    set.add(2);
    set.add(3);
    set.add('a');
    set.add(')');
    Set result;
    //result.complete_set();
    set2 = set.absolute_complement();
    std::cout<<set2.find(4)<<std::endl;
    std::cout<<set2.find(5)<<std::endl;
    std::cout<<set2.find(6)<<std::endl;
    std::cout<<set2.find(2)<<std::endl;
    std::cout<<set2.find(3)<<std::endl;
    std::cout<<set2.find('a')<<std::endl;
    std::cout<<set2.find(')')<<std::endl;
    std::cout<<set2.find(1)<<std::endl;
    std::cout<<set2.find(9)<<std::endl;
    std::cout<<set2.find('g')<<std::endl;


}*/