using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PricingClient
{
    public class Pricer
    {
        public double Price { get; set; }
        public double PriceStdDev { get; set; }
        public List<double> Deltas { get; set; }
        public List<double> DeltasStdDev { get; set; }

        public Pricer(PricingOutput pricingOutput)
        {
            Price = pricingOutput.Price;
            PriceStdDev = pricingOutput.PriceStdDev;
            Deltas = pricingOutput.Deltas.ToList();
            DeltasStdDev = pricingOutput.Deltas.ToList();
        }
    }
}
