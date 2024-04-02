#ifndef TABLE_H
#define TABLE_H


class table
{
    private:
        int column, row;
    public:
        void setColumn(int column)
        {
            this->column = column;
        }
        int getColumn()
        {
            return this->column;
        }
        void setRow(int row)
        {
            this->row = row;
        }
        int getRow()
        {
            return this->row;
        }
};

#endif // TABLE_H
