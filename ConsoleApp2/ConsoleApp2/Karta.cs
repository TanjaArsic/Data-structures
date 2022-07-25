using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2
{
    class Karta
    {
        private string putanja = "D:\\D-dowload\\Karte\\karta";
        private List<int> zabrane;
        public List<int> ruka;
        private bool mf = false;
        private bool ms = false;
        private bool s = false;
        private bool f = false;
        Random rand;
        public Karta()
        {
            rand = new Random();
            zabrane = new List<int>();
            ruka = new List<int>();
        }
        public bool Zabranjeno(int index)
        {
            foreach (int pom in zabrane)
            {
                if (pom == index)
                {
                    return true;
                }
            }
            return false;
        }
        public void izbaci(int index)
        {
            zabrane.RemoveAt(index);
            ruka.RemoveAt(index);
        }
        public string Vrati_putanju()
        {
            int index = rand.Next() % 6 + 1;
            while (Zabranjeno(index))
            {
                index = rand.Next() % 6 + 1;
            }
            zabrane.Add(index);
            ruka.Add(index);
            string pom = putanja + index.ToString() + ".png";
            return pom;
        }
        public int Kvota()
        {
            int suma = 0;
            f = Flush(ruka);
            mf = f;
            if (!mf)
            {
                for (int i = 0; i < 5; i++)
                {
                    if (!mf)
                    {
                        List<int> pomoc = new List<int>();
                        foreach (int vr in ruka)
                        {
                            pomoc.Add(vr);
                        }
                        pomoc.RemoveAt(i);
                        mf = Flush(pomoc);
                    }
                }
            }
            s = Straight(ruka);
            if (!ms)
            {
                for (int i = 0; i < 5; i++)
                {
                    if(!ms)
                    {
                        List<int> pomoc = new List<int>();
                        foreach (int vr in ruka)
                        {
                            pomoc.Add(vr);
                        }
                        pomoc.RemoveAt(i);
                        ms = Mali_Straight(pomoc);
                    }
                }
            }
            if (f && s)
            {
                return 100;
            }
            if (Poker())
            {
                return 60;
            }
            if (ms && mf){
                return 40;
            }
            if (FullHouse()){
                return 24;
            }
            if (f){
                return 16;
            }
            if (s) {
                return 12;
            }
            if (Blaze()){
                return 9;
            }
            if (Triiste()){
                return 6;
            }
            if (Dvapara()){
                return 4;
            }
            if (Par()){
                return 2;
            }
            return 0;
        }
        public bool Flush(List<int> ruka)
        {
            List<int> pom = new List<int>();
            foreach(int vr in ruka)
            {
                pom.Add(vr);
            }
            pom.Sort();
            int max = pom.Max();
            int min = pom.Min();
            if ((min > 0 && max < 14) || (min > 13 && max < 27) || (min > 26 && max < 40) || (min > 39 && max < 53))
            {
                return true;
            }
            return false;
        }
        public bool Straight(List<int> ruka)
        {
            List<int> pom = new List<int>();
            foreach (int vr in ruka)
            {
                pom.Add(vr);
            }
            pom.Sort();
            if ((((pom[0] % 13 + 4) == (pom[1] % 13 + 3)) && ((pom[2] % 13 + 2) == (pom[3] % 13 + 1)) && ((pom[0] % 13 + 4) == (pom[4] % 13 + 0)) && ((pom[0] % 13 + 4) == (pom[2] % 13 + 2))))
            {
                return true;
            }
            if ((pom[4] % 13 == 5) && (pom[0] % 13 == 1) && (pom[1] % 13 == 2) && (pom[2] % 13 == 3) && (pom[3] % 13 == 4))
            {
                return true;
            }
            return false;
        }
        public bool Mali_Straight(List<int> ruka)
        {
            List<int> pom = new List<int>();
            foreach (int vr in ruka)
            {
                pom.Add(vr);
            }
            pom.Sort();
            if ((((pom[0] % 13 + 4) == (pom[1] % 13 + 3)) && ((pom[2] % 13 + 2) == (pom[3] % 13 + 1)) && ((pom[0] % 13 + 4) == (pom[2] % 13 + 2))))
            {
                return true;
            }
            if ((pom[0] % 13 == 1) && (pom[1] % 13 == 2) && (pom[2] % 13 == 3) && (pom[3] % 13 == 4))
            {
                return true;
            }
            return false;
        }
        public bool Poker()
        {
            List<int> pom = new List<int>();
            foreach (int vr in ruka)
            {
                pom.Add(vr % 13);
            }
            if (((pom[0] == pom[1]) && (pom[2] == pom[3]) && (pom[0] == pom[3])) || ((pom[0] == pom[1]) && (pom[2] == pom[4]) && (pom[0] == pom[4])) || ((pom[0] == pom[1]) && (pom[3] == pom[4]) && (pom[0] == pom[4])) || ((pom[0] == pom[2]) && (pom[3] == pom[4]) && (pom[0] == pom[4])) || ((pom[1] == pom[2]) && (pom[3] == pom[4]) && (pom[1] == pom[4])))
            {
                return true;
            }
            return false;
        }
        public bool FullHouse()
        {
            List<int> pom = new List<int>();
            foreach (int vr in ruka)
            {
                pom.Add(vr % 13);
            }
            if (((pom[0] == pom[1]) && (pom[1] == pom[2]) && (pom[3] == pom[4])) || ((pom[0] == pom[1]) && (pom[1] == pom[3]) && (pom[2] == pom[4])) || ((pom[0] == pom[1]) && (pom[1] == pom[4]) && (pom[2] == pom[3])) || ((pom[0] == pom[2]) && (pom[2] == pom[3]) && (pom[1] == pom[4])) || ((pom[0] == pom[2]) && (pom[2] == pom[4]) && (pom[1] == pom[3])) || ((pom[0] == pom[3]) && (pom[3] == pom[4]) && (pom[1] == pom[2])) || ((pom[1] == pom[2]) && (pom[2] == pom[3]) && (pom[0] == pom[4])) || ((pom[1] == pom[2]) && (pom[2] == pom[4]) && (pom[0] == pom[3])) || ((pom[1] == pom[3]) && (pom[3] == pom[4]) && (pom[0] == pom[2])) || ((pom[2] == pom[3]) && (pom[3] == pom[4]) && (pom[0] == pom[1])))
            {
                return true;
            }
            return false;
        }
        public bool Blaze()
        {
            if ((ruka[0] % 13 == 11 || ruka[0] % 13 == 12 || ruka[0] % 13 == 0) && (ruka[1] % 13 == 11 || ruka[1] % 13 == 12 || ruka[1] % 13 == 0) && (ruka[2] % 13 == 11 || ruka[2] % 13 == 12 || ruka[2] % 13 == 0) && (ruka[3] % 13 == 11 || ruka[3] % 13 == 12 || ruka[3] % 13 == 0) && (ruka[4] % 13 == 11 || ruka[4] % 13 == 12 || ruka[4] % 13 == 0))
            {
                return true;
            }
            return false;
        }
        public bool Triiste()
        {
            List<int> pom = new List<int>();
            foreach (int vr in ruka)
            {
                pom.Add(vr % 13);
            }
            if (((ruka[0] == pom[1]) && (pom[1] == pom[2])) || ((pom[0] == pom[1]) && (pom[1] == pom[3])) || ((pom[0] == pom[1]) && (pom[1] == pom[4])) || ((pom[0] == pom[2]) && (pom[2] == pom[3])) || ((pom[0] == pom[2]) && (pom[2] == pom[4])) || ((pom[0] == pom[3]) && (pom[3] == pom[4])) || ((pom[1] == pom[2]) && (pom[2] == pom[3])) || ((pom[1] == pom[2]) && (pom[2] == pom[4])) || ((pom[1] == pom[3]) && (pom[3] == pom[4])) || ((pom[2] == pom[3]) && (pom[3] == pom[4])))
            {
                return true;
            }
            return false;
        }
        public bool Dvapara()
        {
            List<int> pom = new List<int>();
            foreach (int vr in ruka)
            {
                pom.Add(vr % 13);
            }
            if (((pom[0] == pom[1]) && ((pom[2] == pom[3]) || (pom[2] == pom[4]) || (pom[3] == pom[4]))) || ((pom[0] == pom[2]) && ((pom[1] == pom[3]) || (pom[1] == pom[4]) || (pom[3] == pom[4]))) || ((pom[0] == pom[3]) && ((pom[1] == pom[2]) || (pom[1] == pom[4]) || (pom[2] == pom[4]))) || ((pom[0] == pom[4]) && ((pom[1] == pom[2]) || (pom[1] == pom[3]) || (pom[2] == pom[3]))) || ((pom[1] == pom[2]) && ((pom[0] == pom[3]) || (pom[0] == pom[4]) || (pom[3] == pom[4]))) || ((pom[1] == pom[3]) && ((pom[0] == pom[2]) || (pom[0] == pom[4]) || (pom[2] == pom[4]))) || ((pom[1] == pom[4]) && ((pom[0] == pom[2]) || (pom[0] == pom[3]) || (pom[2] == pom[3]))) || ((pom[2] == pom[3]) && ((pom[0] == pom[1]) || (pom[0] == pom[4]) || (pom[1] == pom[4]))) || ((pom[2] == pom[4]) && ((pom[0] == pom[1]) || (pom[0] == pom[3]) || (pom[1] == pom[3]))) || ((pom[3] == pom[4]) && ((pom[0] == pom[1]) || (pom[0] == pom[2]) || (pom[1] == pom[2]))))
            {
                return true;
            }
            return false;
        }
        public bool Par()
        {
            List<int> pom = new List<int>();
            foreach (int vr in ruka)
            {
                pom.Add(vr % 13);
            }
            if ((pom[0] == pom[1]) || (pom[0] == pom[2]) || (pom[0] == pom[3]) || (pom[0] == pom[4]) || (pom[1] == pom[2]) || (pom[1] == pom[3]) || (pom[1] == pom[4]) || (pom[2] == pom[3]) || (pom[2] == pom[4]) || (pom[3] == pom[4]))
            {
                return true;
            }
            return false;
        }
    }
}
