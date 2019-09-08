//
// Created by friday on 2019/9/4.
//

#ifndef BPPTREE_BPPTREE_H
#define BPPTREE_BPPTREE_H

#include <vector>
#include <set>
#include <ostream>
#include <iostream>
#include <json/value.h>

namespace bpptree{




    template <typename TYPE, size_t M = 1024, typename Compare = std::less<TYPE> >
    struct node {
        typedef TYPE  type;

        typedef typename std::set<type, Compare>::const_iterator const_iterator;
        typedef typename std::set<type, Compare>::iterator       iterator;



        node(){}

        node(const std::set<type, Compare> &v){
            values = v;
        }

        node(std::set<type, Compare> &&v){
            values.insert(v);
        }

        template <typename Begin, typename End>
        node(Begin begin, End end){
            values.insert(begin, end);
        }



        void insert(const type &v){
            if(values.size() == M){
                values.insert(v);

                node<TYPE, M, Compare> node_front;
                node<TYPE, M, Compare> node_back;
                const size_t  mid = (values.size() + 1) / 2;
                size_t i = 0;
                TYPE t;
                for(auto begin = values.begin(); begin != values.end(); i++, begin++){
                    if(i < mid){
                        node_front.insert(*begin);
                    }
                    else if(i == mid){
                        t = *begin;
                    }
                    else if(i > mid){
                        node_back.insert(*begin);
                    }
                }
                values.clear();
                values.insert(t);

                assert(node_front.values.size() > 0 && node_back.values.size() > 0);
                node_front.depth = depth + 1;
                node_back.depth = depth + 1;
                children.push_back(node_front);
                children.push_back(node_back);
                return;
            }

            if(values.size() > 0 && !compare(*values.begin(), v)){
                if(children.size() > 0){
                    auto &front = children[0];
                    front.insert(v);
                }
                else{
                   values.insert(v);
                }
            }
            else if(values.size() > 0 && compare(*values.rbegin(), v)){
                if(children.size() == M + 1){
                    auto &back = children[children.size() - 1];
                    back.insert(v);
                }
                else{
                    values.insert(v);
                }
            }
            else{
                size_t  i = 0;
                for(auto itr = values.begin(); itr != values.end(); itr++, i++){
                    if(!compare(*itr, v)){
                        break;
                    }
                }
                if(i >= children.size()){
                    values.insert(v);
                }
                else{
                    children[i].insert(v);
                }
            }
        }

        bool remove(const type &&v){

            return true;
        }




        const_iterator begin() const{

        }

        const_iterator end() const{

        }


        void debug(Json::Value &vv){
           size_t i = 0;
           for(auto itr = values.begin(); itr != values.end(); itr++, i++){
                vv["value" + std::to_string(i)] = itr->to_string();
           }

           i = 0;
           for(auto itr : children){
               Json::Value dp;
               children[i].debug(dp);
               vv[std::to_string(i) + "depth " + std::to_string(children[i].depth)] = dp;
               i++;
           }
        }


    private:


        size_t                                  depth = 0;
        Compare                                 compare;
        std::set<type, Compare>                 values;
        std::vector< node<TYPE, M, Compare>>    children;
    };



//    template <typename TYPE, size_t M = 1024, typename Compare = std::less<TYPE>>
//    struct leaf : public node<TYPE, M, Compare>{
//
//    };









}

#endif //BPPTREE_BPPTREE_H
